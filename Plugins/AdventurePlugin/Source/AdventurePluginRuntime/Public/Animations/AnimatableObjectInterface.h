#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "AnimatableObjectInterface.generated.h"

class UAdventurePluginGameContext;

/**
* Delegate to call when an animation finishes. 
* @param AnimationName The name of the finished animation.
* @param Sender The object on which the animation was run.
* @param CompletedSuccesfully True if animation was found on the object and executed to finish, otherwise false. 
*/
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAnimationCompletedEvent, FName, AnimationName, UObject*, Sender, bool, bCompletedSuccessfully);

/**
* Interface for a class representing an object that can be animated. @see IAnimatableObjectInterface
*/
UINTERFACE(BlueprintType)
class ADVENTUREPLUGINRUNTIME_API UAnimatableObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
* Interface for a class representing an object that can be animated. An animated object should control animations on its own.
* So if the object is moving, it should switch to a moving animation, if the object is idle it should play idle animation.
* This interface is here to allow other objects to explicitly state that they want some animation performed.
* It is written mainly for dialogs, so the interface also has methods for retrieving talking states.
*/
class ADVENTUREPLUGINRUNTIME_API IAnimatableObjectInterface
{
	GENERATED_BODY()

public:
	/**
	* Retrieves all animation states this object supports.
	* @return All of the animation states this object supports.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Animations")
	TArray<FName> GetAllAnimationStates();

	/**
	* Retrieves all animation states this objects supports that can be used as a talking animation - e.g. Angry, Crying etc.
	* Should be a subset of GetAllAnimationStates().
	* @return All the talking animation states of this object.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Animations")
	TArray<FName> GetTalkingStates();

	/**
	* Retrieves the default animation state of the object, i.e. which talking animation should be used if no specific talking animation is specified.
	* Should be an element from GetTalkingStates().
	* @return The default talking state.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Animations")
	FName GetDefaultTalkingAnimationState();

	/**
	* Sets an animation state on this object. 
	* Expected behavior is that the object should continue doing this animation until either another call to SetAnimationState()
	* changes the state or ResetAnimationState() clears the state and returns the control over animations to this object.
	* @param AnimationName The name of the animation state that should be set. Should be an element from GetAllAnimationStates().
	* @return True if the animation state was found on the object and started succesfully, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Animations")
	bool SetAnimationState(FName AnimationName);

	/**
	* Resets the animation state on this object. The object should start managing its own animations again.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Animations")
	void ResetAnimationState();

	/**
	* Tells the object to play an animation once and call a callback once finished, either successfully on unsuccessfuly.
	* @param AnimationName The name of the animation to be played once. Should be an element from GetAllAnimationStates().
	* @param Callback The delegate that should be called once this animation is finished. Not guaranteed to be bound.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Animations")
	void PlayAnimation(FName AnimationName, const FAnimationCompletedEvent& Callback);
};
