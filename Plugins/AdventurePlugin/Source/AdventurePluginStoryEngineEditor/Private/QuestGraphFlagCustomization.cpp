#include "QuestGraphFlagCustomization.h"
#include "StoryEngine/Structs/QuestGraphFlag.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "StoryEngine/Graph/QuestGraphNode_Flag.h"
//#include "Widgets/Text/STextBlock.h"
//#include "IDetailChildrenBuilder.h"
//#include "DetailWidgetRow.h"

TSharedRef<IPropertyTypeCustomization> FQuestGraphFlagCustomization::MakeInstance()
{
	return MakeShareable(new FQuestGraphFlagCustomization);
}

TSharedPtr<IPropertyHandle> FQuestGraphFlagCustomization::GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphFlag, Quest));
}

TSharedPtr<IPropertyHandle> FQuestGraphFlagCustomization::GetNamePropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphFlag, FlagName));
}

void FQuestGraphFlagCustomization::ReloadOptions()
{
	if (GraphHandle.IsValid())
	{
		UObject* QuestObj;
		GraphHandle->GetValue(QuestObj);
		UQuestGraph* Quest = Cast<UQuestGraph>(QuestObj);
		if (Quest && Quest->IsValidLowLevel())
		{
			for (UGenericGraphNode* Node : Quest->AllNodes)
			{
				auto* FlagNode = Cast<UQuestGraphNode_Flag>(Node);
				if (FlagNode)
				{
					Options.Add(MakeShareable(new FName(FlagNode->FlagName)));
				}
			}
		}
	}
}

/*

#define LOCTEXT_NAMESPACE "QuestGraphFlagCustomization"

TSharedRef<IPropertyTypeCustomization> FQuestGraphFlagCustomization::MakeInstance()
{
	return MakeShareable(new FQuestGraphFlagCustomization);
}

void FQuestGraphFlagCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	FText Desc = GetHeaderRowName(StructPropertyHandle);
	
	if (!Desc.IsEmpty())
	{
		HeaderRow.NameContent()
			[
				StructPropertyHandle->CreatePropertyNameWidget()
			]
		.ValueContent()
			.MaxDesiredWidth(400.0f)
			[
				SNew(STextBlock)
				.Text(Desc)
			.Font(StructCustomizationUtils.GetRegularFont())
			];
	}
}

FText FQuestGraphFlagCustomization::GetHeaderRowName(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	TSharedPtr<IPropertyHandle> QHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphFlag, Quest));
	TSharedPtr<IPropertyHandle> FNHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphFlag, FlagName));

	FText Desc = LOCTEXT("InvalidFlag", "<Empty>");

	if (QHandle.IsValid() && FNHandle.IsValid())
	{
		UObject* Obj;
		QHandle->GetValue(Obj);
		UQuestGraph* Quest = Cast<UQuestGraph>(Obj);
		FName FlagName;
		FNHandle->GetValue(FlagName);
		if (Quest && Quest->IsValidLowLevel() && !FlagName.IsNone())
		{		
			Desc = FText::Format(FText::FromString("{0}->{1}"), FText::FromString(Quest->Name), FText::FromName(FlagName));
		}
	}

	return Desc;
}

TSharedRef<SWidget> FQuestGraphFlagCustomization::MakeWidgetForName(FComboItemType InOption)
{
	return SNew(STextBlock).Text(FText::FromName(*InOption));
}

void FQuestGraphFlagCustomization::OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type)
{
	if (FlagNameHandle.IsValid())
	{
		FlagNameHandle->SetValue(NewValue.IsValid() ? *NewValue : FName());
	}
}

FText FQuestGraphFlagCustomization::GetCurrentItemLabel() const
{
	if (FlagNameHandle.IsValid())
	{
		FName FlagName;
		FlagNameHandle->GetValue(FlagName);
		if (FlagName.IsValid())
		{
			return FText::FromName(FlagName);
		}
	}

	return LOCTEXT("InvalidComboEntryText", "<Empty>");
}

void FQuestGraphFlagCustomization::ReloadComboBox()
{
	FQuestGraphFlagCustomization::ReloadComboBox(FName());
}

void FQuestGraphFlagCustomization::ReloadComboBox(FName Name)
{
	Options.Empty();
	FComboItemType Selected;

	if (QuestHandle.IsValid())
	{
		UObject* QuestObj;
		QuestHandle->GetValue(QuestObj);
		UQuestGraph* Quest = Cast<UQuestGraph>(QuestObj);
		if (Quest && Quest->IsValidLowLevel())
		{
			for (UGenericGraphNode* Node : Quest->AllNodes)
			{
				auto* FlagNode = Cast<UQuestGraphNode_Flag>(Node);
				if (FlagNode)
				{
					FComboItemType Item = MakeShareable(new FName(FlagNode->FlagName));
					if (!Name.IsNone() && Name.IsEqual(FlagNode->FlagName)) Selected = Item;
					Options.Add(Item);
				}
			}
		}
	}

	if (Name.IsNone() && FlagNameHandle.IsValid())
	{
		FlagNameHandle->ResetToDefault();
	}

	ComboBox->RefreshOptions();
	ComboBox->SetSelectedItem(Selected);
}

void FQuestGraphFlagCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	QuestHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphFlag, Quest));
	FlagNameHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FQuestGraphFlag, FlagName));

	StructBuilder.AddProperty(QuestHandle.ToSharedRef());

	QuestHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FQuestGraphFlagCustomization::ReloadComboBox));

	FName FlagName;
	FlagNameHandle->GetValue(FlagName);

	FDetailWidgetRow& ComboBoxRow = StructBuilder.AddCustomRow(LOCTEXT("FlagName", "Flag name"));
	
	ComboBoxRow.NameContent()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("FlagName", "Flag name"))
		];
	
	ComboBoxRow.ValueContent()
		[
			SAssignNew(ComboBox, SComboBox<FComboItemType>)
			.OptionsSource(&Options)
			.OnSelectionChanged(this, &FQuestGraphFlagCustomization::OnSelectionChanged)
			.OnGenerateWidget(this, &FQuestGraphFlagCustomization::MakeWidgetForName)
			//.InitiallySelectedItem(Options[0])
			[
				SNew(STextBlock)
				.Text(this, &FQuestGraphFlagCustomization::GetCurrentItemLabel)
			]
		];

	ReloadComboBox(FlagName);
}

#undef LOCTEXT_NAMESPACE
*/