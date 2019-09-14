#pragma once

#include "AdventurePluginRuntime.h"
#include "Common/AdventurePluginGameContext.h"
#include "Common/AdventurePluginConfig.h"
#include "Dialog/Graph/DialogGraph.h"
#include "Dialog/Graph/DialogGraphNode.h"
#include "Dialog/Presenter/DialogPresenterInterface.h"
#include "Kismet/GameplayStatics.h"
#include "DialogController.generated.h"

/**
* A delegate for notifications fired when something dialog related happens.
* @param Dialog The dialog this notification is about.
* @param GameContext Provides access to all Adventure Plugin data and functionality.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDialogNotification, UDialogGraph*, Dialog, UAdventurePluginGameContext*, GameContext);

/**
 * This class can walk through the UDialogGraph and play a dialog that corresponds to it.
 * It is started from some specific node called an entry point.
 * On each node the UDialogController calls the UDialogGraphNode#Execute method, which should do whatever is the node supposed to be doing, for example showing dialog line to the player.
 * When node execution is complete, the controller will call UDialogGraphNode#GetNextNode on that node to get the next node to execute.
 * If UDialogGraphNode#GetNextNode returns null, we have reached the end of dialog.
 * <p>
 * Most nodes finish instantly, but some do not. For those the UDialogGraphNode#Execute method returns false, signalling that we should halt the execution.
 * The dialog can be continued by calling some callback method defined on this object.
 * For example, setting a variable finishes instantly, but showing a dialog line does not. 
 * Instead, the execution will continue once the presenter calls the proper callback on this object.
 * When the callback is called, the controller will check whether the current node also responds to that callback. 
 * If it does, it asks the node to handle that callback and see whether it can continue or not.
 * Also, the dialog can also end automatically once too many nodes are executed, assuming we are in an infinite loop.
 */
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogController : public UObject
{
	GENERATED_BODY()

public:

	/**
	* This event is raised when a dialog is started.
	*/
	UPROPERTY(BlueprintAssignable, Category = "Adventure Plugin|Dialog")
	FDialogNotification DialogStarted;

	/**
	* This event is raised when a dialog ends. 
	*/
	UPROPERTY(BlueprintAssignable, Category = "Adventure Plugin|Dialog")
	FDialogNotification DialogEnded;

	/**
	* Starts the specified dialog from the main entry point.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param DialogGraph The dialog graph to be started.
	*/
	virtual void ShowDialog(UAdventurePluginGameContext* GameContext, UDialogGraph* DialogGraph);

	/**
	* Starts the specified dialog from the specified node.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param DialogGraph The dialog graph to be started.
	* @param StartNode The node from which the execution should be started.
	*/
	virtual void ShowDialog(UAdventurePluginGameContext* GameContext, UDialogGraph* DialogGraph, UDialogGraphNode* StartNode);

	/**
	* Ends the dialog.
	*/
	virtual void HideDialog();

	/**
	* Should be called by presenter when showing of a line, both PC and NPC, is over.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Dialog")
	virtual void ShowDialogLineCallback();

	/**
	* Should be called by presenter when the user selects a dialog option.
	* @param SelectedOptionIndex The index of the option the user selected.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Dialog")
	virtual void ShowDialogLineSelectionCallback(int32 SelectedOptionIndex);

	/**
	* Should be called by presenter when an animation finishes.
	* @param AnimationName The name of the animation that finished.
	* @param bSuccess If true, the animation played successfully from start to finish, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Dialog")
	virtual void PlayAnimationCallback(FName AnimationName, bool bSuccess);

	/**
	* If true, a dialog is currently being executed.
	*/
	UPROPERTY(BlueprintReadOnly, Transient, Category = "Adventure Plugin|Dialog")
	bool bIsShowingDialog;

	/**
	* The dialog graph being executed.
	*/
	UPROPERTY(BlueprintReadOnly, Transient, Category = "Adventure Plugin|Dialog")
	UDialogGraph* CurrentGraph;

	/**
	* The game context used in the current execution.
	*/
	UPROPERTY(Transient)
	UAdventurePluginGameContext* CurrentGameContext;

protected:

	/**
	* Where we are in the execution. When null, no dialog is in progress.
	*/
	UPROPERTY(Transient)
	UDialogGraphNode* CurrentNode;

	/**
	* Starts executing the graph from the specified node.
	* @param StartNode Where should the execution start.
	*/
	virtual void BeginExecute(UDialogGraphNode* StartNode);

	/**
	* Retrieves the presenter we are using
	* @return The instance of the currently used presenter.
	*/
	FORCEINLINE IDialogPresenterInterface* GetPresenter()
	{
		return IsValid(CurrentGameContext) ? Cast<IDialogPresenterInterface>(CurrentGameContext->DialogPresenter.GetObject()) : nullptr;
	}

	/**
	* How many steps since BeginExecute() was last called. Used so we can stop execution if we're in an infinite loop.
	*/
	uint32 CurrentExecutionSteps;

	/**
	* A fallback for infinite cycles - if the dialog execution takes more than this amount of steps, we'll assume we are in an infinite cycle.
	*/
	static const uint32 MaxExecutionSteps = 100000;
};
