// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueController.h"

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

		// todo øídit nìjakým nastavením z defaultù, každá hra to mùže mít jinak
		controller->SetInputMode(Mode);
		controller->SetIgnoreMoveInput(true);
		controller->bShowMouseCursor = true;

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


	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Has proper Instance."));

	//for (auto i : graph->AllNodes)
	//{
	//	auto dn = Cast<UDialogGraphNode>(i);
	//	if (dn)
	//	{
	//		print(dn->DialogText.ToString());

	//		for (auto children : dn->ChildrenNodes)
	//		{
	//			auto childrenDN = Cast<UDialogGraphNode>(children);
	//			if (childrenDN)
	//			{
	//				print(TEXT("Found children!"));
	//				print(childrenDN->DialogText.ToString());
	//			}
	//		}
	//	}
	//	else
	//		printR(TEXT("Node is not type of DialogGraphNOde"));
	//}

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

		// todo øídit nìjakým nastavením z defaultù, každá hra to mùže mít jinak
		FInputModeGameOnly Mode;
		controller->SetInputMode(Mode);
		controller->SetIgnoreMoveInput(false);
		controller->bShowMouseCursor = false;

		auto pawn = UGameplayStatics::GetPlayerPawn(world, 0);
		pawn->EnableInput(controller);
	}
}



void UDialogueController::beginExecute(UDialogGraphNode* node)
{
	if (!node || !node->IsValidLowLevel())
	{
		// TODO we should do something?
		return;
	}

	node->Execute(this, presenterInstance);
}

#pragma optimize("", on)