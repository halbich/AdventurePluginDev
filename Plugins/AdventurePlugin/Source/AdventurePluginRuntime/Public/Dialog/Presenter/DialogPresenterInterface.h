// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UniquePtr.h"
#include "Structs/DialogLineData.h"
#include "DialogPresenterInterface.generated.h"

class UDialogGraphNode;
class UDialogController;
class IAnimatableObjectInterface;

/**
 * @see IDialogPresenterInterface
 */
UINTERFACE(BlueprintType)
class ADVENTUREPLUGINRUNTIME_API UDialogPresenterInterface : public UInterface
{
	GENERATED_BODY()


};
/**
* Defines all methods that must be present on a dialog presenter.
*/
class IDialogPresenterInterface
{
	GENERATED_BODY()

public:
	/**
	* Changes the visibility of the presenter.
	* @param bVisible If true the presenter should be shown, if false it should be hidden.
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Dialog")
	void SetPresenterVisibility(bool bVisible);
	/**
	* Shows a dialog line to the user.
	* @param DialogLineData The dialog line to be displayed.
	* @param DialogController The dialog controller that initiated this call. A callback should be called on that controller when the dialog line disappears.
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Dialog")
	void ShowDialogLine(FDialogLineData DialogLineData, UDialogController* DialogController);
	/**
	* Shows a couple of dialog options the player can choose from.
	* @param Options The dialog line to be displayed.
	* @param DialogController The dialog controller that initiated this call. A callback should be called on that controller when the users selects an option.
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Dialog")
	void ShowDialogSelection(UPARAM(ref) TArray<FDialogLineData>& Options, UDialogController* DialogController);
	/**
	* Plays an animation on the specified object once.
	* @param AnimationTarget The object which should play the animation.
	* @param AnimationName The animation that should be played.
	* @param DialogController The dialog controller that initiated this call. A callback should be called on that controller when the animation finishes.
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Dialog")
	void PlayAnimationOnce(const TScriptInterface<IAnimatableObjectInterface>& AnimationTarget, FName AnimationName, UDialogController* DialogController);
	/**
	* Sets the animation state of the animated object.
	* @param AnimationTarget The object which should play the animation.
	* @param AnimationName The animation that should be played.
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Dialog")
	void SetAnimationState(const TScriptInterface<IAnimatableObjectInterface>& AnimationTarget, FName AnimationName);
	/**
	* Resets the animation state of the object, giving it back control over its animations.
	* @param AnimationTarget The object which should play the animation.
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Dialog")
	void ResetAnimationState(const TScriptInterface<IAnimatableObjectInterface>& AnimationTarget);
};
