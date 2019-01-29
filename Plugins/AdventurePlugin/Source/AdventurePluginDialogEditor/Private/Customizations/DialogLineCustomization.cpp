#include "Customizations/DialogLineCustomization.h"
#include "Dialogue/Graph/DialogGraphNode_DialogLineBase.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "DialogLineCustomization"

#pragma optimize("", off)
TSharedRef<IDetailCustomization> FDialogLineCustomization::MakeInstance()
{
	return MakeShareable(new FDialogLineCustomization);
}

void FDialogLineCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	IdHandle = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogGraphNode_DialogLineBase, AnimationName));
	DetailLayout.HideProperty(IdHandle);
	FName Id;
	IdHandle->GetValue(Id);

	FDetailWidgetRow& ComboBoxRow = DetailLayout.AddCustomRowToCategory(IdHandle, LOCTEXT("TalkingAnimation", "Talking Animation"));

	ComboBoxRow.NameContent()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("TalkingAnimation", "Talking Animation"))
		];

	TSharedPtr<SComboBox<FComboItemType>> ComboBox;

	ComboBoxRow.ValueContent()
		[
			SAssignNew(ComboBox, SComboBox<FComboItemType>)
			.OptionsSource(&Options)
		.OnSelectionChanged(this, &FDialogLineCustomization::OnSelectionChanged)
		.OnGenerateWidget(this, &FDialogLineCustomization::MakeWidgetForName)
		[
			SNew(STextBlock)
			.Text(this, &FDialogLineCustomization::GetCurrentItemLabel)
		]
		];

	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailLayout.GetObjectsBeingCustomized(Objects);

	if (Objects.Num() > 0)
	{
		UDialogGraphNode_DialogLineBase* DialogNode = Cast<UDialogGraphNode_DialogLineBase>(Objects[0]);
		auto animatedCharacter = DialogNode && DialogNode->IsValidLowLevel() ? DialogNode->GetSpeakerEditorOnly() : nullptr;
		if (animatedCharacter != nullptr)
		{
			TSet<FComboItemType> Ids;
			FComboItemType SelectedId;
			auto allAnimationStates = animatedCharacter->Execute_GetTalkingStates(animatedCharacter);
			for (auto animationState : allAnimationStates)
			{
				FComboItemType NewItem = MakeShareable(new FName(animationState));
				if (animationState == Id) SelectedId = NewItem;
				Ids.Add(NewItem);
			}
			Options = Ids.Array();
			ComboBox->RefreshOptions();
			ComboBox->SetSelectedItem(SelectedId);
		}
	}
}

FText FDialogLineCustomization::GetCurrentItemLabel() const
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

TSharedRef<SWidget> FDialogLineCustomization::MakeWidgetForName(FComboItemType InOption)
{
	return SNew(STextBlock).Text(FText::FromName(*InOption));
}

void FDialogLineCustomization::OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type)
{
	if (IdHandle.IsValid())
	{
		IdHandle->SetValue(NewValue.IsValid() ? *NewValue : FName());
	}
}

#undef LOCTEXT_NAMESPACE 

#pragma optimize("", on)