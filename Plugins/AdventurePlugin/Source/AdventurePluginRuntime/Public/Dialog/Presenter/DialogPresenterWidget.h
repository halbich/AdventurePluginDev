#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dialog/Graph/DialogGraphNode.h"
#include "DialogPresenterInterface.h"
#include "DialogPresenterWidget.generated.h"

/**
* Class responsible for showing dialog lines to the user. It has no behavior by default and must be overriden in blueprints.
*/
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UDialogPresenterWidget : public UUserWidget, public IDialogPresenterInterface
{
	GENERATED_BODY()

public:

	/**
	* Changes the visibility of the presenter.
	* @param bVisible If true the presenter should be shown, if false it should be hidden.
	*/
	void SetPresenterVisibility(bool bVisible);

	/**
	* Shows a dialog line to the user.
	* @param DialogLineData The dialog line to be displayed.
	* @param DialogController The dialog controller that initiated this call. A callback should be called on that controller when the dialog line disappears.
	*/
	void ShowDialogLine(FDialogLineData DialogLineData, UDialogController* DialogController);
	
	/**
	* Shows a couple of dialog options the player can choose from.
	* @param Options The dialog line to be displayed.
	* @param DialogController The dialog controller that initiated this call. A callback should be called on that controller when the users selects an option.
	*/
	void ShowDialogSelection(TArray<FDialogLineData>& Options, UDialogController* DialogController);
	
	/**
	* Plays an animation on the specified object once.
	* @param AnimationTarget The object which should play the animation.
	* @param AnimationName The animation that should be played.
	* @param DialogController The dialog controller that initiated this call. A callback should be called on that controller when the animation finishes.
	*/
	void PlayAnimationOnce(const TScriptInterface<IAnimatableObjectInterface>& AnimationTarget, FName AnimationName, UDialogController* DialogController);
	
	/**
	* Sets the animation state of the animated object.
	* @param AnimationTarget The object which should play the animation.
	* @param AnimationName The animation that should be played.
	*/
	void SetAnimationState(const TScriptInterface<IAnimatableObjectInterface>& AnimationTarget, FName AnimationName);
	
	/**
	* Resets the animation state of the object, giving it back control over its animations.
	* @param AnimationTarget The object which should play the animation.
	*/
	void ResetAnimationState(const TScriptInterface<IAnimatableObjectInterface>& AnimationTarget);
};
