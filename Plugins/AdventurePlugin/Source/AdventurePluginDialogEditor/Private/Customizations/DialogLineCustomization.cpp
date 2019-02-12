#include "Customizations/DialogLineCustomization.h"
#include "Dialog/Graph/BaseClasses/DialogGraphNode_DialogLineBase.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "DialogLineCustomization"


TSharedRef<IDetailCustomization> FDialogLineCustomization::MakeInstance()
{
	return MakeShareable(new FDialogLineCustomization);
}
void FDialogLineCustomization::SetIdHandle(IDetailLayoutBuilder& DetailLayout)
{
	IdHandle = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogGraphNode_DialogLineBase, AnimationName));
}
FText FDialogLineCustomization::GetComboBoxName()
{
	return LOCTEXT("TalkingAnimation", "Talking Animation");
}
TSet<FComboBoxCustomization::FComboItemType> FDialogLineCustomization::GetComboBoxOptions(UObject* ObjectBeingCustomized)
{
	TSet<FComboItemType> TalkingAnimationStates;
	UDialogGraphNode_DialogLineBase* DialogNode = Cast<UDialogGraphNode_DialogLineBase>(ObjectBeingCustomized);
	UAdventureCharacter* AnimatedCharacter = DialogNode && DialogNode->IsValidLowLevel() ? DialogNode->GetSpeakerEditorOnly() : nullptr;
	if (!IsValid(AnimatedCharacter))
	{
		return TalkingAnimationStates;
	}
	TArray<FName> TalkingAnimationStateNames = AnimatedCharacter->Execute_GetTalkingStates(AnimatedCharacter);
	for (FName& AnimationStateName : TalkingAnimationStateNames)
	{
		FComboItemType NewItem = MakeShareable(new FName(AnimationStateName));
		TalkingAnimationStates.Add(NewItem);
	}
	return TalkingAnimationStates;
}

#undef LOCTEXT_NAMESPACE 