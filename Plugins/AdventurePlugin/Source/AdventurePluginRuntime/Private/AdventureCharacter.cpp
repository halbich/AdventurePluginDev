#include "AdventureCharacter.h"
#include "AdventurePluginRuntime.h"


UTexture2D* UAdventureCharacter::GetIcon() const
{
	return Icon;
}
// MARK: IAnimatableObjectInterface Implementation
TArray<FName> UAdventureCharacter::GetAllAnimationStates_Implementation()
{
	return AnimationStates;
}

TArray<FName> UAdventureCharacter::GetTalkingStates_Implementation()
{
	return TalkingAnimationStates;
}

FName UAdventureCharacter::GetDefaultTalkingAnimationState_Implementation()
{
	return DefaultTalkingAnimationState;
}

bool UAdventureCharacter::SetAnimationState_Implementation(FName Animation)
{
	if (!bIsAnimatable || !IsActorProperlyBound() || !IsAnimationNameValid(Animation))
	{
		return false;
	}
	SetAnimationStateEvent.Broadcast(Animation);
	return true;
}

void UAdventureCharacter::ResetAnimationState_Implementation()
{
	if (!bIsAnimatable || !IsActorProperlyBound())
	{
		return;
	}
	ResetAnimationStateEvent.Broadcast();
}
void UAdventureCharacter::PlayAnimation_Implementation(FName Animation, const FAnimationCompletedEvent& Callback)
{
	if (!bIsAnimatable || !IsActorProperlyBound() || !IsAnimationNameValid(Animation))
	{
		Callback.ExecuteIfBound(Animation, this, false);
		return;
	}
	if (CurrentPlayAnimationCallback.IsBound())
	{
		// We are interrupting old animation, so it will not be properly finished.
		CurrentPlayAnimationCallback.Execute(CurrentPlayAnimationName, this, false);
		CurrentPlayAnimationCallback.Clear();
	}
	CurrentPlayAnimationCallback = Callback;
	CurrentPlayAnimationName = Animation;
	PlayAnimationOnceEvent.Broadcast(Animation);
}

void UAdventureCharacter::AnimationFinished(FName AnimationName)
{
	if (!CurrentPlayAnimationCallback.IsBound() || AnimationName != CurrentPlayAnimationName)
	{
		return;
	}
	CurrentPlayAnimationCallback.Execute(AnimationName, this, true);
	CurrentPlayAnimationCallback.Clear();
	CurrentPlayAnimationName = FName();
}
bool UAdventureCharacter::IsActorProperlyBound()
{
	if (!SetAnimationStateEvent.IsBound() || !ResetAnimationStateEvent.IsBound() || !PlayAnimationOnceEvent.IsBound())
	{
		LOG_Error(NSLOCTEXT("AP", "AnimationActorNotBound.", "No actor bound to UAdventureCharacter, animation state cannot be changed."));
		return false;
	}
	return true;
}

bool UAdventureCharacter::IsAnimationNameValid(FName AnimationName)
{
	if (!AnimationStates.Contains(AnimationName))
	{
		auto warningText = FText::Format(NSLOCTEXT("AP", "InvalidAnimationState", "Animation state {0} not found."),
			FText::FromName(AnimationName));
		LOG_Error(warningText);
		return false;
	}
	return true;
}