#pragma once

#include "Core.h"
#include "Classes/Engine/DataAsset.h"
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Animations/AnimatableObjectInterface.h"
#include "CombinableObject.h"
#include "Delegate.h"
#include "AdventureCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAnimationEvent, FName, AnimationName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResetAnimationEvent);

UCLASS(BlueprintType)
class ADVENTUREPLUGINRUNTIME_API UAdventureCharacter : public UCombinableObject, public IIconThumbnailInterface, public IAnimatableObjectInterface
{
	//GENERATED_USTRUCT_BODY()
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsPlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* Icon;
	// MARK: Animations
	
	//This event is fired when the actor representing this object is supposed to play a specific animation once. Call AnimationFinished once the animation is finished.
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
		FAnimationEvent PlayAnimationOnceEvent;

	//This event is called whenever the actor representing this object is supposed to play an animation in a loop until the animation state is changed or canceled. 
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
		FAnimationEvent SetAnimationStateEvent;

	//This event is called whenever the actor representing this object is supposed to stop playing animations requested by this object and start doing whatever it wants, usually playing an idle animation. 
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
		FResetAnimationEvent ResetAnimationStateEvent;

	// Contains all animation states defined on this character.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FName> AnimationStates;

	// Subset of AnimationStates, should contain all animations that can be used while talking, mainly emotions.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FName> TalkingAnimationStates;

	// From TalkingAnimationStates, contains the animation that should be shown while talking if no other animation is specified.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName DefaultTalkingAnimationState;
	// Call when the animation requested by this class is finished.
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Animations")
		void AnimationFinished(FName AnimationName);

	// MARK: IIconThumbnailInterface implementation
	virtual UTexture2D* GetIcon() const override;
	// MARK: IAnimatableObjectInterface Implementation
	virtual TArray<FName> GetAllAnimationStates_Implementation();

	virtual TArray<FName> GetTalkingStates_Implementation();

	virtual FName GetDefaultTalkingAnimationState_Implementation();

	virtual bool SetAnimationState_Implementation(FName Animation);

	virtual void ResetAnimationState_Implementation();
	virtual void PlayAnimation_Implementation(FName Animation, const FAnimationCompletedEvent& Callback);
private:
	// Makes sure that an actor is bound to all animation events and if not, display an error. Returns true if it is, otherwise false.
	bool IsActorProperlyBound();
	bool IsAnimationNameValid(FName AnimationName);

	UPROPERTY(Transient)
		FAnimationCompletedEvent CurrentPlayAnimationCallback;

	UPROPERTY(Transient)
		FName CurrentPlayAnimationName;
};