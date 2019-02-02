// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogController.h"
#include "NodeInterfaces/DialogNodeShowLineCallbackInterface.h"
#include "NodeInterfaces/DialogNodeShowOptionsCallbackInterface.h"
#include "NodeInterfaces/DialogNodePlayAnimationCallbackInterface.h"

#pragma optimize("", off)

void UDialogController::ShowDialog(UAdventurePluginGameContext* gameContext, UDialogGraph* graph)
{
	ShowDialog(gameContext, graph, graph->MainEntryPoint);
}

void UDialogController::ShowDialog(UAdventurePluginGameContext* gameContext, UDialogGraph* graph, UDialogGraphNode* startNode)
{
	currentContext = gameContext;
	CurrentGraph = graph;

	if (startNode == NULL || startNode->ChildrenNodes.Num() == 0)
	{
		LOG_Error(NSLOCTEXT("AP", "startNodeNull", "Show dialog::startNode is NULL"));
		return;
	}

	beginExecute(startNode);

	auto presenterInstance = presenter();
	if (presenterInstance)
		IDialogPresenterInterface::Execute_SetPresenterVisibility(presenterInstance->_getUObject(), true);
}

void UDialogController::HideDialog()
{
	auto presenterInstance = presenter();
	if (presenterInstance)
		IDialogPresenterInterface::Execute_SetPresenterVisibility(presenterInstance->_getUObject(), false);

	currentContext = NULL;
}

void UDialogController::beginExecute(UDialogGraphNode* node)
{
	currentNode = node;

	while (currentNode && currentNode->IsValidLowLevel() && currentNode->Execute(currentContext)) {
		currentNode = currentNode->GetNextNode(currentContext);
	}
	if (currentNode && currentNode->IsValidLowLevel()) {
		// Dialog not over yet, waiting for further input.
		return;
	}
	// End of dialog
	HideDialog();
}

void UDialogController::ShowDialogLineCallback()
{
	if (currentNode && currentNode->GetClass()->ImplementsInterface(UDialogNodeShowLineCallbackInterface::StaticClass())) {
		if (IDialogNodeShowLineCallbackInterface::Execute_ShowDialogLineCallback(currentNode, this)) {
			// The node responds to the callback and wishes to continue dialogue execution.
			beginExecute(currentNode->GetNextNode(currentContext));
		}
	}
}

void UDialogController::ShowDialogLineSelectionCallback(int32 selectedOptionIndex)
{
	if (currentNode && currentNode->GetClass()->ImplementsInterface(UDialogNodeShowOptionsCallbackInterface::StaticClass())) {
		if (IDialogNodeShowOptionsCallbackInterface::Execute_DialogOptionSelected(currentNode, selectedOptionIndex, this)) {
			// The node responds to the callback and wishes to continue dialogue execution.
			beginExecute(currentNode->GetNextNode(currentContext));
		}
	}
}

UFUNCTION(BlueprintCallable, Category = "Dialog")
void UDialogController::PlayAnimationCallback(FName AnimationName, bool Success)
{
	if (currentNode && currentNode->GetClass()->ImplementsInterface(UDialogNodePlayAnimationCallbackInterface::StaticClass())) {
		if (IDialogNodePlayAnimationCallbackInterface::Execute_PlayAnimationCallback(currentNode, AnimationName, Success)) {
			// The node responds to the callback and wishes to continue dialogue execution.
			beginExecute(currentNode->GetNextNode(currentContext));
		}
	}
}

#pragma optimize("", on)