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
	currentPresenter = currentContext->DialoguePresenter;
	CurrentGraph = graph;

	if (startNode == NULL || startNode->ChildrenNodes.Num() == 0)
	{
		// TODO report error
		return;
	}

	beginExecute(startNode);

	if (presenter())
	{
		auto obj = currentContext->DialoguePresenter.GetObject();
		IDialoguePresenterInterface::Execute_SetPresenterVisibility(obj, true);
	}
}

void UDialogueController::HideDialog()
{
	if (presenter())
	{
		auto obj = currentContext->DialoguePresenter.GetObject();
		IDialoguePresenterInterface::Execute_SetPresenterVisibility(obj, false);
	}
}

void UDialogueController::beginExecute(UDialogGraphNode* node)
{
	currentNode = node;

	while (currentNode && currentNode->IsValidLowLevel() && currentNode->Execute(this, presenter())) {
		currentNode = currentNode->GetNextNode(this);
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
			beginExecute(currentNode->GetNextNode(this));
		}
	}
}

void UDialogueController::ShowDialogLineSelectionCallback(UObject* WorldContextObject, int32 selectedOptionIndex)
{
	if (currentNode && currentNode->GetClass()->ImplementsInterface(UDialogueNodeShowOptionsCallbackInterface::StaticClass())) {
		if (IDialogueNodeShowOptionsCallbackInterface::Execute_DialogueOptionSelected(currentNode, selectedOptionIndex, this)) {
			// The node responds to the callback and wishes to continue dialogue execution.
			beginExecute(currentNode->GetNextNode(this));
		}
	}
}

#pragma optimize("", on)