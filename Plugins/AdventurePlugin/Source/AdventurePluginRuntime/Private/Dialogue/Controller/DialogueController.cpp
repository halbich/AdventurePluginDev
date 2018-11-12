// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueController.h"
#include "NodeInterfaces/DialogueNodeShowLineCallbackInterface.h"
#include "NodeInterfaces/DialogueNodeShowOptionsCallbackInterface.h"

#pragma optimize("", off)

void UDialogueController::ShowDialog(UAdventurePluginGameContext* gameContext, UDialogGraph* graph)
{
	ShowDialog(gameContext, graph, graph->MainEntryPoint);
}

void UDialogueController::ShowDialog(UAdventurePluginGameContext* gameContext, UDialogGraph* graph, UDialogGraphNode* startNode)
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
		IDialoguePresenterInterface::Execute_SetPresenterVisibility(presenterInstance->_getUObject(), true);
}

void UDialogueController::HideDialog()
{
	auto presenterInstance = presenter();
	if (presenterInstance)
		IDialoguePresenterInterface::Execute_SetPresenterVisibility(presenterInstance->_getUObject(), false);

	currentContext = NULL;
}

void UDialogueController::beginExecute(UDialogGraphNode* node)
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

void UDialogueController::ShowDialogLineCallback(UObject* WorldContextObject)
{
	if (currentNode && currentNode->GetClass()->ImplementsInterface(UDialogueNodeShowLineCallbackInterface::StaticClass())) {
		if (IDialogueNodeShowLineCallbackInterface::Execute_ShowDialogueLineCallback(currentNode, this)) {
			// The node responds to the callback and wishes to continue dialogue execution.
			beginExecute(currentNode->GetNextNode(currentContext));
		}
	}
}

void UDialogueController::ShowDialogLineSelectionCallback(UObject* WorldContextObject, int32 selectedOptionIndex)
{
	if (currentNode && currentNode->GetClass()->ImplementsInterface(UDialogueNodeShowOptionsCallbackInterface::StaticClass())) {
		if (IDialogueNodeShowOptionsCallbackInterface::Execute_DialogueOptionSelected(currentNode, selectedOptionIndex, this)) {
			// The node responds to the callback and wishes to continue dialogue execution.
			beginExecute(currentNode->GetNextNode(currentContext));
		}
	}
}

#pragma optimize("", on)