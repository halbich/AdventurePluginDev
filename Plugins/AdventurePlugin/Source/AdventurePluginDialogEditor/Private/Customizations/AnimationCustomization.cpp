#include "Customizations/AnimationCustomization.h"
#include "Dialogue/Graph/DialogGraphNode_PlayAnimationBase.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "AnimationCustomization"

#pragma optimize("", off)
TSharedRef<IDetailCustomization> FAnimationCustomization::MakeInstance()
{
	return MakeShareable(new FAnimationCustomization);
}

void FAnimationCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	IdHandle = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogGraphNode_PlayAnimationBase, AnimationName));
	DetailLayout.HideProperty(IdHandle);
	FName Id;
	IdHandle->GetValue(Id);

	FDetailWidgetRow& ComboBoxRow = DetailLayout.AddCustomRowToCategory(IdHandle, LOCTEXT("AnimationName", "Animation"));

	ComboBoxRow.NameContent()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("AnimationName", "Animation"))
		];

	TSharedPtr<SComboBox<FComboItemType>> ComboBox;

	ComboBoxRow.ValueContent()
		[
			SAssignNew(ComboBox, SComboBox<FComboItemType>)
			.OptionsSource(&Options)
		.OnSelectionChanged(this, &FAnimationCustomization::OnSelectionChanged)
		.OnGenerateWidget(this, &FAnimationCustomization::MakeWidgetForName)
		[
			SNew(STextBlock)
			.Text(this, &FAnimationCustomization::GetCurrentItemLabel)
		]
		];

	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailLayout.GetObjectsBeingCustomized(Objects);

	if (Objects.Num() > 0)
	{
		UDialogGraphNode_PlayAnimationBase* AnimationNode = Cast<UDialogGraphNode_PlayAnimationBase>(Objects[0]);
		auto animatedObject = AnimationNode && AnimationNode->IsValidLowLevel() ? AnimationNode->GetEditorTimeAnimatableObject() : nullptr;
		if (animatedObject != nullptr)
		{
			TSet<FComboItemType> Ids;
			FComboItemType SelectedId;
			auto allAnimationStates = animatedObject->Execute_GetAllAnimationStates(animatedObject.GetObject());
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

FText FAnimationCustomization::GetCurrentItemLabel() const
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

TSharedRef<SWidget> FAnimationCustomization::MakeWidgetForName(FComboItemType InOption)
{
	return SNew(STextBlock).Text(FText::FromName(*InOption));
}

void FAnimationCustomization::OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type)
{
	if (IdHandle.IsValid())
	{
		IdHandle->SetValue(NewValue.IsValid() ? *NewValue : FName());
	}
}

#undef LOCTEXT_NAMESPACE 

#pragma optimize("", on)