#include "Customizations/AnimationCustomization.h"
#include "Dialog/Graph/BaseClasses/DialogGraphNode_PlayAnimationBase.h"

#define LOCTEXT_NAMESPACE "AnimationCustomization"

TSharedRef<IDetailCustomization> FAnimationCustomization::MakeInstance()
{
	return MakeShareable(new FAnimationCustomization);
}

TSharedPtr<IPropertyHandle> FAnimationCustomization::GetIdPropertyHandle(IDetailLayoutBuilder& DetailLayout) const
{
	return DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogGraphNode_PlayAnimationBase, AnimationName));
}

FText FAnimationCustomization::GetComboBoxName() const
{
	return LOCTEXT("AnimationName", "Animation");
}

void FAnimationCustomization::ReloadOptions()
{
	UDialogGraphNode_PlayAnimationBase* AnimationNode = Cast<UDialogGraphNode_PlayAnimationBase>(ObjectBeingCustomized);
	TScriptInterface<IAnimatableObjectInterface> AnimatedObject = IsValid(AnimationNode) ? AnimationNode->GetEditorTimeAnimatableObject() : nullptr;
	if (IsValid(AnimatedObject.GetObject()))
	{
		TArray<FName> AllAnimationStateNames = AnimatedObject->Execute_GetAllAnimationStates(AnimatedObject.GetObject());
		for (FName AnimationStateName : AllAnimationStateNames)
		{
			FComboItemType NewItem = MakeShareable(new FName(AnimationStateName));
			Options.Add(NewItem);
		}
	}
}

#undef LOCTEXT_NAMESPACE 
