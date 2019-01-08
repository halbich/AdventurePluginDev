#include "Customizations/APSaveGameCustomization.h"
#include "AdventurePluginSaveGame.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SComboBox.h"

#define LOCTEXT_NAMESPACE "FAPSaveGameCustomization"

TSharedRef<IDetailCustomization> FAPSaveGameCustomization::MakeInstance()
{
	return MakeShareable(new FAPSaveGameCustomization);
}

void FAPSaveGameCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	IdHandle = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UAdventurePluginSaveGame, SaveUserIndex));
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
		.OnSelectionChanged(this, &FAPSaveGameCustomization::OnSelectionChanged)
		.OnGenerateWidget(this, &FAPSaveGameCustomization::MakeWidgetForName)
		[
			SNew(STextBlock)
			.Text(this, &FAPSaveGameCustomization::GetCurrentItemLabel)
		]
		];

	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailLayout.GetObjectsBeingCustomized(Objects);

	if (Objects.Num() > 0)
	{
		TSet<FComboItemType> Ids;
		FComboItemType SelectedId;

		FComboItemType NewItem = MakeShareable(new FName("test"));
		Ids.Add(NewItem);
		Ids.Add(MakeShareable(new FName(Id)));

		Options = Ids.Array();
		ComboBox->RefreshOptions();
		ComboBox->SetSelectedItem(SelectedId);


		/*UDialogGraphNode_Goto* GotoNode = Cast<UDialogGraphNode_Goto>(Objects[0]);
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
		*/
	}
}

FText FAPSaveGameCustomization::GetCurrentItemLabel() const
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

TSharedRef<SWidget> FAPSaveGameCustomization::MakeWidgetForName(FComboItemType InOption)
{
	return SNew(STextBlock).Text(FText::FromName(*InOption));
}

void FAPSaveGameCustomization::OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type)
{
	if (IdHandle.IsValid())
	{
		IdHandle->SetValue(NewValue.IsValid() ? *NewValue : FName());
	}
}

#undef LOCTEXT_NAMESPACE 