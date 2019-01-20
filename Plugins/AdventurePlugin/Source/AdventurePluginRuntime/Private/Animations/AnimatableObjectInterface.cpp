#include "Animations/AnimatableObjectInterface.h"

TArray<FName> IAnimatableObjectInterface::GetAllAnimationStates_Implementation()
{
	return TArray<FName>();
}

TArray<FName> IAnimatableObjectInterface::GetTalkingStates_Implementation()
{
	return TArray<FName>();
}

FText IAnimatableObjectInterface::GetDefaultTalkingAnimationState_Implementation()
{
	return FText();
}

bool IAnimatableObjectInterface::SetAnimationState_Implementation(FName Animation)
{
	return false;
}

void IAnimatableObjectInterface::ResetAnimationState_Implementation()
{

}

void IAnimatableObjectInterface::PlayAnimation_Implementation(FName Animation, const FAnimationCompletedEvent& Callback)
{
	Callback.Execute(Animation, nullptr, false);
}