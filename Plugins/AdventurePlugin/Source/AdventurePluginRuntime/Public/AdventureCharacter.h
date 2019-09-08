#pragma once

#include "Core.h"
#include "Engine/DataAsset.h"
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Animations/AnimatableObjectInterface.h"
#include "CombinableObject.h"
#include "Delegate.h"
#include "AdventureCharacter.generated.h"

/**
* A delegate for events to be fired when animation should be played.
* @param AnimationName The name of the animation that should be played.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAnimationEvent, FName, AnimationName);

/**
* A delegate for Reset animation event. 
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResetAnimationEvent);

/**
* Class defining a character in game. Each subclass should define a single game character.
* There should always be only one instance of each character at a time.
* Important - this is not an actual character in the scene. This object has information that is independent on the scene.
* It mainly exists because of dialogs, so we can define who is speaking and to get their icons.
* It also contains a really simple animation system. It is possible to set animation to be played in a loop, stop playing animations and to play an animation once.
* This class raises events that some animations should happen, but does nothing directly.
* A character object on the scene is expected to bind to these events and respond to them.
* @see UAdventureCharacterBlueprint
*/
UCLASS(Abstract, BlueprintType)
class ADVENTUREPLUGINRUNTIME_API UAdventureCharacter : public UCombinableObject, public IIconThumbnailInterface, public IAnimatableObjectInterface
{
	GENERATED_BODY()

public:

	/**
	* Human friendly name of this character.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Adventure Plugin")
	FText Name;

	/**
	* If true, this character can be a player character.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Adventure Plugin")
	bool bIsPlayerCharacter;

	/**
	* The icon representing this character, used by editor, but it can also be accessed in game if needed.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Adventure Plugin")
	UTexture2D* Icon;

	// MARK: Animations
	/**
	* If false, this object does not use the animation system. Animations should do nothing and no animation warnings should ever be fired. 
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Adventure Plugin")
	bool bIsAnimatable = true;
	
	/**
	* This event is fired when the actor representing this object is supposed to play a specific animation once. Call AnimationFinished() once the animation is finished.
	*/
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, Category = "Adventure Plugin")
	FAnimationEvent PlayAnimationOnceEvent;

	/**
	* This event is called whenever the actor representing this object is supposed to play an animation in a loop until the animation state is changed or canceled. 
	*/
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, Category = "Adventure Plugin")
	FAnimationEvent SetAnimationStateEvent;

	/**
	* This event is called whenever the actor representing this object is supposed to stop playing animations requested by this object and start doing whatever it wants, usually playing an idle animation. 
	*/
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, Category = "Adventure Plugin")
	FResetAnimationEvent ResetAnimationStateEvent;

	/**
	* Contains all animation states defined on this character.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Adventure Plugin")
	TArray<FName> AnimationStates;

	/**
	* Subset of UAdventureCharacter#AnimationStates, should contain all animations that can be used while talking, mainly emotions.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Adventure Plugin")
	TArray<FName> TalkingAnimationStates;

	/**
	* From UAdventureCharacter#TalkingAnimationStates, contains the animation that should be shown while talking if no other animation is specified.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Adventure Plugin")
	FName DefaultTalkingAnimationState;

	/**
	* This method must be called by actor when an animation requested by this class is finished.
	* @param AnimationName The animation that finished.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Animations")
	void AnimationFinished(FName AnimationName);

	// MARK: IIconThumbnailInterface implementation
	virtual UTexture2D* GetIcon() const override;

	// MARK: IAnimatableObjectInterface Implementation
	/**
	* @see IAnimatableObjectInterface#GetAllAnimationStates
	*/
	virtual TArray<FName> GetAllAnimationStates_Implementation();

	/**
	* @see IAnimatableObjectInterface#GetTalkingStates
	*/
	virtual TArray<FName> GetTalkingStates_Implementation();

	/**
	* @see IAnimatableObjectInterface#GetDefaultTalkingAnimationState
	*/
	virtual FName GetDefaultTalkingAnimationState_Implementation();

	/**
	* @see IAnimatableObjectInterface#SetAnimationState
	*/
	virtual bool SetAnimationState_Implementation(FName Animation);

	/**
	* @see IAnimatableObjectInterface#ResetAnimationState
	*/
	virtual void ResetAnimationState_Implementation();

	/**
	* @see IAnimatableObjectInterface#PlayAnimation
	*/
	virtual void PlayAnimation_Implementation(FName Animation, const FAnimationCompletedEvent& Callback);

protected:
	/**
	* Makes sure that an actor is bound to all animation events and if not, display an error.
	* @return True if it is, otherwise false.
	*/
	bool IsActorProperlyBound();

	/**
	* Checks whether the animation name is valid, i.e. if it is one of the animation states the object supports.
	* @param AnimationName The animation to check.
	* @return True if the animation name is valid.
	*/
	bool IsAnimationNameValid(FName AnimationName);

	/**
	* A callback to call once an animation that is being played finishes.
	* The callback is from the IAnimatableObjectInterface#PlayAnimation method.
	*/
	UPROPERTY(Transient)
	FAnimationCompletedEvent CurrentPlayAnimationCallback;

	/**
	* The animation that is currently being played.
	*/
	UPROPERTY(Transient)
	FName CurrentPlayAnimationName;
};