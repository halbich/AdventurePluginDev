#include "Customizations/DialogLineCustomization.h"
#include "Dialog/Graph/BaseClasses/DialogGraphNode_DialogLineBase.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "DialogLineCustomization"

TSharedRef<IDetailCustomization> FDialogLineCustomization::MakeInstance()
{
	return MakeShareable(new FDialogLineCustomization);
}

TSharedPtr<IPropertyHandle> FDialogLineCustomization::GetIdPropertyHandle(IDetailLayoutBuilder& DetailLayout) const
{
	return DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogGraphNode_DialogLineBase, AnimationName));
}

FText FDialogLineCustomization::GetComboBoxName() const
{
	return LOCTEXT("TalkingAnimation", "Talking Animation");
}

void FDialogLineCustomization::ReloadOptions()
{
	UDialogGraphNode_DialogLineBase* DialogNode = Cast<UDialogGraphNode_DialogLineBase>(ObjectBeingCustomized);
	UAdventureCharacter* AnimatedCharacter = IsValid(DialogNode)? DialogNode->GetSpeakerEditorOnly() : nullptr;
	if (IsValid(AnimatedCharacter))
	{
		TArray<FName> TalkingAnimationStateNames = AnimatedCharacter->Execute_GetTalkingStates(AnimatedCharacter);
		for (FName& AnimationStateName : TalkingAnimationStateNames)
		{
			FComboItemType NewItem = MakeShareable(new FName(AnimationStateName));
			Options.Add(NewItem);
		}
	}
}

#undef LOCTEXT_NAMESPACE 