#include "Customizations/AnimationCustomization.h"
#include "Dialog/Graph/BaseClasses/DialogGraphNode_PlayAnimationBase.h"

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
	TSet<FComboItemType> AllAnimationStates;
	UDialogGraphNode_PlayAnimationBase* AnimationNode = Cast<UDialogGraphNode_PlayAnimationBase>(ObjectBeingCustomized);
	TScriptInterface<IAnimatableObjectInterface> AnimatedObject = AnimationNode && AnimationNode->IsValidLowLevel() ? AnimationNode->GetEditorTimeAnimatableObject() : nullptr;
	if (!IsValid(AnimatedObject.GetObject()))
	{
		return AllAnimationStates;
	}
	TArray<FName> AllAnimationStateNames = AnimatedObject->Execute_GetAllAnimationStates(AnimatedObject.GetObject());
	for (FName AnimationStateName : AllAnimationStateNames)
	{
		FComboItemType NewItem = MakeShareable(new FName(AnimationStateName));
		AllAnimationStates.Add(NewItem);
	}
	return AllAnimationStates;
}

#undef LOCTEXT_NAMESPACE 
