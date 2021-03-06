#include "Dialog/Controller/DialogController.h"
#include "Dialog/NodeInterfaces/DialogNodeShowLineCallbackInterface.h"
#include "Dialog/NodeInterfaces/DialogNodeShowOptionsCallbackInterface.h"
#include "Dialog/NodeInterfaces/DialogNodePlayAnimationCallbackInterface.h"

void UDialogController::ShowDialog(UAdventurePluginGameContext* GameContext, UDialogGraph* DialogGraph, UObject* WorldContextObject)
{
	ShowDialog(GameContext, DialogGraph, DialogGraph->MainEntryPoint, WorldContextObject);
}

void UDialogController::ShowDialog(UAdventurePluginGameContext* GameContext, UDialogGraph* DialogGraph, UDialogGraphNode* StartNode, UObject* WorldContextObject)
{
	auto* world = WorldContextObject ? WorldContextObject->GetWorld() : nullptr;
	auto* gameInstance = world ? world->GetGameInstance() : nullptr;
	CachedGameInstance = MakeWeakObjectPtr(gameInstance);
	if (StartNode == nullptr || StartNode->ChildrenNodes.Num() == 0)
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogController_ShowDialog_StartNodeNull", "Show dialog::StartNode is NULL"));
		return;
	}
	if (bIsShowingDialog)
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogController_ShowDialog_Dialog in progress", "Show dialog::Another dialog is already being executed. Cannot execute another dialog."));
		return;
	}
	CurrentGameContext = GameContext;
	CurrentGraph = DialogGraph;
	CurrentGraph->CachedGameInstance = MakeWeakObjectPtr(gameInstance);
	bIsShowingDialog = true;
	DialogStarted.Broadcast(DialogGraph, GameContext);
	IDialogPresenterInterface* PresenterInstance = GetPresenter();

	if (PresenterInstance)
	{
		IDialogPresenterInterface::Execute_SetPresenterVisibility(PresenterInstance->_getUObject(), true);
	}
	BeginExecute(StartNode);
}

void UDialogController::HideDialog()
{
	IDialogPresenterInterface* PresenterInstance = GetPresenter();
	if (PresenterInstance)
	{
		IDialogPresenterInterface::Execute_SetPresenterVisibility(PresenterInstance->_getUObject(), false);
	}

	DialogEnded.Broadcast(CurrentGraph, CurrentGameContext);
	CurrentGameContext = nullptr;
	CurrentGraph = nullptr;
	bIsShowingDialog = false;
}

void UDialogController::BeginExecute(UDialogGraphNode* StartNode)
{
	CurrentExecutionSteps = 0;
	CurrentNode = StartNode;

	while (IsValid(CurrentNode) && CurrentNode->Execute(CurrentGameContext))
	{
		CurrentNode = CurrentNode->GetNextNode(CurrentGameContext);
		if (++CurrentExecutionSteps >= MaxExecutionSteps)
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogController_DialogExecutionStuck", "BeginExecute: Dialog is probably stuck in a loop, breaking it by force. Reason - running too long."));
			CurrentNode = nullptr;
			break;
		}
	}
	if (IsValid(CurrentNode))
	{
		// Dialog not over yet, waiting for further input.
		return;
	}
	// End of dialog
	HideDialog();
}

void UDialogController::ShowDialogLineCallback()
{
	if (CurrentNode && CurrentNode->GetClass()->ImplementsInterface(UDialogNodeShowLineCallbackInterface::StaticClass()))
	{
		if (IDialogNodeShowLineCallbackInterface::Execute_ShowDialogLineCallback(CurrentNode, this))
		{
			// The node responds to the callback and wishes to continue dialogue execution.
			BeginExecute(CurrentNode->GetNextNode(CurrentGameContext));
		}
	}
}

void UDialogController::ShowDialogLineSelectionCallback(int32 SelectedOptionIndex)
{
	if (CurrentNode && CurrentNode->GetClass()->ImplementsInterface(UDialogNodeShowOptionsCallbackInterface::StaticClass()))
	{
		if (IDialogNodeShowOptionsCallbackInterface::Execute_DialogOptionSelected(CurrentNode, SelectedOptionIndex, this))
		{
			// The node responds to the callback and wishes to continue dialogue execution.
			BeginExecute(CurrentNode->GetNextNode(CurrentGameContext));
		}
	}
}

void UDialogController::PlayAnimationCallback(FName AnimationName, bool bSuccess)
{
	if (CurrentNode && CurrentNode->GetClass()->ImplementsInterface(UDialogNodePlayAnimationCallbackInterface::StaticClass()))
	{
		if (IDialogNodePlayAnimationCallbackInterface::Execute_PlayAnimationCallback(CurrentNode, AnimationName, bSuccess))
		{
			// The node responds to the callback and wishes to continue dialogue execution.
			BeginExecute(CurrentNode->GetNextNode(CurrentGameContext));
		}
	}
}
