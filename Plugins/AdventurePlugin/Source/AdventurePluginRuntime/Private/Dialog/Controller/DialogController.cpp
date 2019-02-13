// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogController.h"
#include "NodeInterfaces/DialogNodeShowLineCallbackInterface.h"
#include "NodeInterfaces/DialogNodeShowOptionsCallbackInterface.h"
#include "NodeInterfaces/DialogNodePlayAnimationCallbackInterface.h"

#pragma optimize("", off)

void UDialogController::ShowDialog(UAdventurePluginGameContext* GameContext, UDialogGraph* DialogGraph)
{
	ShowDialog(GameContext, DialogGraph, DialogGraph->MainEntryPoint);
}

void UDialogController::ShowDialog(UAdventurePluginGameContext* GameContext, UDialogGraph* DialogGraph, UDialogGraphNode* StartNode)
{
	CurrentGameContext = GameContext;
	CurrentGraph = DialogGraph;

	if (StartNode == nullptr || StartNode->ChildrenNodes.Num() == 0)
	{
		LOG_Error(NSLOCTEXT("AP", "startNodeNull", "Show dialog::startNode is NULL"));
		return;
	}

	BeginExecute(StartNode);
	IDialogPresenterInterface* PresenterInstance = GetPresenter();

	if (PresenterInstance)
	{
		IDialogPresenterInterface::Execute_SetPresenterVisibility(PresenterInstance->_getUObject(), true);
	}
}

void UDialogController::HideDialog()
{
	IDialogPresenterInterface* PresenterInstance = GetPresenter();
	if (PresenterInstance)
	{
		IDialogPresenterInterface::Execute_SetPresenterVisibility(PresenterInstance->_getUObject(), false);
	}

	CurrentGameContext = nullptr;
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
			LOG_Error(NSLOCTEXT("AP", "DialogExecutionStuck", "BeginExecute: Dialog is probably stuck in a loop, breaking in by force. Reason - running too long."));
			CurrentNode = nullptr;
			break;
		}
	}
	if (IsValid(CurrentNode)) {
		// Dialog not over yet, waiting for further input.
		return;
	}
	// End of dialog
	HideDialog();
}

void UDialogController::ShowDialogLineCallback()
{
	if (CurrentNode && CurrentNode->GetClass()->ImplementsInterface(UDialogNodeShowLineCallbackInterface::StaticClass())) {
		if (IDialogNodeShowLineCallbackInterface::Execute_ShowDialogLineCallback(CurrentNode, this)) {
			// The node responds to the callback and wishes to continue dialogue execution.
			BeginExecute(CurrentNode->GetNextNode(CurrentGameContext));
		}
	}
}

void UDialogController::ShowDialogLineSelectionCallback(int32 SelectedOptionIndex)
{
	if (CurrentNode && CurrentNode->GetClass()->ImplementsInterface(UDialogNodeShowOptionsCallbackInterface::StaticClass())) {
		if (IDialogNodeShowOptionsCallbackInterface::Execute_DialogOptionSelected(CurrentNode, SelectedOptionIndex, this)) {
			// The node responds to the callback and wishes to continue dialogue execution.
			BeginExecute(CurrentNode->GetNextNode(CurrentGameContext));
		}
	}
}

void UDialogController::PlayAnimationCallback(FName AnimationName, bool bSuccess)
{
	if (CurrentNode && CurrentNode->GetClass()->ImplementsInterface(UDialogNodePlayAnimationCallbackInterface::StaticClass())) {
		if (IDialogNodePlayAnimationCallbackInterface::Execute_PlayAnimationCallback(CurrentNode, AnimationName, bSuccess)) {
			// The node responds to the callback and wishes to continue dialogue execution.
			BeginExecute(CurrentNode->GetNextNode(CurrentGameContext));
		}
	}
}

#pragma optimize("", on)