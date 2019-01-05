#include "Customizations/GotoCustomization.h"
#include "Dialogue/Graph/DialogGraphNode_Goto.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "GotoCustomization"

TSharedRef<IDetailCustomization> FGotoCustomization::MakeInstance()
{
	return MakeShareable(new FGotoCustomization);
}

void FGotoCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	IdHandle = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogGraphNode_Goto, TargetNodeId));
	DetailLayout.HideProperty(IdHandle);
	FName Id;
	IdHandle->GetValue(Id);

	FDetailWidgetRow& ComboBoxRow = DetailLayout.AddCustomRowToCategory(IdHandle, LOCTEXT("TargetNodeId", "Target Node Id"));

	ComboBoxRow.NameContent()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("TargetNodeId", "Target Node Id"))
		];

	TSharedPtr<SComboBox<FComboItemType>> ComboBox;

	ComboBoxRow.ValueContent()
		[
			SAssignNew(ComboBox, SComboBox<FComboItemType>)
			.OptionsSource(&Options)
			.OnSelectionChanged(this, &FGotoCustomization::OnSelectionChanged)
			.OnGenerateWidget(this, &FGotoCustomization::MakeWidgetForName)
			[
				SNew(STextBlock)
				.Text(this, &FGotoCustomization::GetCurrentItemLabel)
			]
		];

	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailLayout.GetObjectsBeingCustomized(Objects);

	if (Objects.Num() > 0)
	{
		UDialogGraphNode_Goto* GotoNode = Cast<UDialogGraphNode_Goto>(Objects[0]);
		if (GotoNode && GotoNode->IsValidLowLevel() && GotoNode->Graph && GotoNode->Graph->IsValidLowLevel())
		{
			TSet<FComboItemType> Ids;
			FComboItemType SelectedId;
			for (auto Node : GotoNode->Graph->AllNodes)
			{
				UDialogGraphNode* GraphNode = Cast<UDialogGraphNode>(Node);
				if (GraphNode && GraphNode->IsValidLowLevel() && !GraphNode->Id.IsNone())
				{
					FComboItemType NewItem = MakeShareable(new FName(GraphNode->Id));
					if (GraphNode->Id == Id) SelectedId = NewItem;
					Ids.Add(NewItem);
				}
			}
			Options = Ids.Array();
			ComboBox->RefreshOptions();
			ComboBox->SetSelectedItem(SelectedId);
		}
	}
}

FText FGotoCustomization::GetCurrentItemLabel() const
{
	if (IdHandle.IsValid())
	{
		FName Name;
		IdHandle->GetValue(Name);
		if (Name.IsValid())
		{
			return FText::FromName(Name);
		}
	}

	return LOCTEXT("InvalidComboEntryText", "<Empty>");
}

TSharedRef<SWidget> FGotoCustomization::MakeWidgetForName(FComboItemType InOption)
{
	return SNew(STextBlock).Text(FText::FromName(*InOption));
}

void FGotoCustomization::OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type)
{
	if (IdHandle.IsValid())
	{
		IdHandle->SetValue(NewValue.IsValid() ? *NewValue : FName());
	}
}

#undef LOCTEXT_NAMESPACE 