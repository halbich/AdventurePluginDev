// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegate.h"
#include "Interface.h"
#include "AnimatableObjectInterface.generated.h"

class UAdventurePluginGameContext;
/*Delegate to call when an animation finishes. AnimationName is the name of the finished animation, sender is the class that caused it and CompletedSuccesfully is true if animation was found on the object and executed to finish, otherwise false. */
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAnimationCompletedEvent, FName, AnimationName, UObject*, Sender, bool, CompletedSuccessfully);

/**
*A class implementing this interface represents a combination, i.e. that some object can be combined with another object and that combination will cause something will happen.
*/
UINTERFACE(BlueprintType)
class ADVENTUREPLUGINRUNTIME_API UAnimatableObjectInterface : public UInterface
{
	GENERATED_BODY()


};

class ADVENTUREPLUGINRUNTIME_API IAnimatableObjectInterface
{
	GENERATED_BODY()

public:
	/*Returns all animation states supported by this object.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Animations")
		TArray<FName> GetAllAnimationStates();

	/*Returns all animation states that can be used for talking animatins - angry, happy, etc.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Animations")
		TArray<FName> GetTalkingStates();

	/* Return the talking animation state that should be used if no other animation state is specified. Should also be returned in GetTalkingStates method.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Animations")
		FName GetDefaultTalkingAnimationState();

	/*Tells the actor represented by this object to change its animation state to some specific state. Returns false if the change cannot be made, for example because animation state does not exist.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Animations")
		bool SetAnimationState(FName Animation);

	/*Resets the animation state of the represented actor to the default one, usually an idle animation.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Animations")
		void ResetAnimationState();

	/*Play the specified animation once, calling Callback once the animation finishes.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Animations")
		void PlayAnimation(FName Animation, const FAnimationCompletedEvent& Callback);
};
