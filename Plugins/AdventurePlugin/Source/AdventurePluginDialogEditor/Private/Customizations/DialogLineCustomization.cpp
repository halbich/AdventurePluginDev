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
	TSet<FComboItemType> Ids;
	UDialogGraphNode_DialogLineBase* DialogNode = Cast<UDialogGraphNode_DialogLineBase>(ObjectBeingCustomized);
	auto* animatedCharacter = DialogNode && DialogNode->IsValidLowLevel() ? DialogNode->GetSpeakerEditorOnly() : nullptr;
	if (!IsValid(animatedCharacter))
	{
		return Ids;
	}
	auto allAnimationStates = animatedCharacter->Execute_GetTalkingStates(animatedCharacter);
	for (auto animationState : allAnimationStates)
	{
		FComboItemType NewItem = MakeShareable(new FName(animationState));
		Ids.Add(NewItem);
	}
	return Ids;
}

#undef LOCTEXT_NAMESPACE 