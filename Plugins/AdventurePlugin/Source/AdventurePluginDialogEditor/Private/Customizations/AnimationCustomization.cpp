#include "Customizations/AnimationCustomization.h"
#include "Dialogue/Graph/BaseClasses/DialogGraphNode_PlayAnimationBase.h"

#define LOCTEXT_NAMESPACE "AnimationCustomization"

TSharedRef<IDetailCustomization> FAnimationCustomization::MakeInstance()
{
	return MakeShareable(new FAnimationCustomization);
}
void FAnimationCustomization::SetIdHandle(IDetailLayoutBuilder& DetailLayout)
{
	IdHandle = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogGraphNode_PlayAnimationBase, AnimationName));
}
FText FAnimationCustomization::GetComboBoxName()
{
	return LOCTEXT("AnimationName", "Animation");
}
TSet<FComboBoxCustomization::FComboItemType> FAnimationCustomization::GetComboBoxOptions(UObject* ObjectBeingCustomized)
{
	TSet<FComboItemType> Ids;
	UDialogGraphNode_PlayAnimationBase* AnimationNode = Cast<UDialogGraphNode_PlayAnimationBase>(ObjectBeingCustomized);
	auto animatedObject = AnimationNode && AnimationNode->IsValidLowLevel() ? AnimationNode->GetEditorTimeAnimatableObject() : nullptr;
	if (!IsValid(animatedObject.GetObject()))
	{
		return Ids;
	}
	auto allAnimationStates = animatedObject->Execute_GetAllAnimationStates(animatedObject.GetObject());
	for (auto animationState : allAnimationStates)
	{
		FComboItemType NewItem = MakeShareable(new FName(animationState));
		Ids.Add(NewItem);
	}
	return Ids;
}

#undef LOCTEXT_NAMESPACE 
