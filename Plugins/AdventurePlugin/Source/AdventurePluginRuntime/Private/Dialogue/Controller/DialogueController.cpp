// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueController.h"
#include "NodeInterfaces/DialogueNodeShowLineCallbackInterface.h"
#include "NodeInterfaces/DialogueNodeShowOptionsCallbackInterface.h"

#pragma optimize("", off)

void UDialogueController::ShowDialog(UDialogGraph* graph, UGameInstance* instance)
{
	cachedGameInstance = instance;

	if (!presenterInstance || !presenterInstance->IsValidLowLevel())
	{
		auto cdo = DefaultPresenter.Get();
		if (cdo)
			presenterInstance = CreateWidget<UDialoguePresenterWidget>(instance, cdo);

		if (!presenterInstance || !presenterInstance->IsValidLowLevel())
			setDefaulPresenterInstance(instance);

		if (!presenterInstance || !presenterInstance->IsValidLowLevel())
		{
			// TODO log error
			return;
		}
	}

	if (cachedGameInstance && cachedGameInstance->IsValidLowLevel())
	{
		auto world = cachedGameInstance->GetWorld();


		FInputModeUIOnly Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

		// TODo get player index
		auto controller = UGameplayStatics::GetPlayerController(world, 0);

		/* todo øídit nìjakým nastavením z defaultù, každá hra to mùže mít jinak *
		controller->SetInputMode(Mode);
		controller->SetIgnoreMoveInput(true);
		controller->bShowMouseCursor = true;
		/**/

		auto pawn = UGameplayStatics::GetPlayerPawn(world, 0);
		pawn->DisableInput(controller);
	}

	UGenericGraphNode* currentRoot = NULL;
	for (auto root : graph->RootNodes)
	{
		// TODO find actual starting point
		if (true)
		{
			currentRoot = root;
		}
	}

	if (currentRoot == NULL)
	{
		// TODO report error
		return;
	}

	auto rootChildren = currentRoot->ChildrenNodes[0];
	auto ourRoot = Cast<UDialogGraphNode>(rootChildren);

	beginExecute(ourRoot);


	presenterInstance->AddToViewport(0);
}

void UDialogueController::HideDialog()
{
	if (presenterInstance && presenterInstance->IsValidLowLevel())
		presenterInstance->RemoveFromViewport();

	if (cachedGameInstance && cachedGameInstance->IsValidLowLevel())
	{
		auto world = cachedGameInstance->GetWorld();
		auto controller = UGameplayStatics::GetPlayerController(world, 0);

		/* todo øídit nìjakým nastavením z defaultù, každá hra to mùže mít jinak *
		FInputModeGameOnly Mode;
		controller->SetInputMode(Mode);
		controller->SetIgnoreMoveInput(false);
		controller->bShowMouseCursor = false;
		/**/

		auto pawn = UGameplayStatics::GetPlayerPawn(world, 0);
		pawn->EnableInput(controller);
	}
}



void UDialogueController::beginExecute(UDialogGraphNode* node)
{
	currentNode = node;
	while (currentNode && currentNode->IsValidLowLevel() && currentNode->Execute(this, presenterInstance)) {
		currentNode = currentNode->GetNextNode();
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
			beginExecute(currentNode->GetNextNode());
		}
	}
}

void UDialogueController::ShowDialogLineSelectionCallback(UObject* WorldContextObject, int32 selectedOptionIndex)
{
	if (currentNode && currentNode->GetClass()->ImplementsInterface(UDialogueNodeShowOptionsCallbackInterface::StaticClass())) {

		if (IDialogueNodeShowOptionsCallbackInterface::Execute_DialogueOptionSelected(currentNode, selectedOptionIndex, this)) {
			// The node responds to the callback and wishes to continue dialogue execution.
			beginExecute(currentNode->GetNextNode());
		}
	}
}

#pragma optimize("", on)