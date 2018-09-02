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

#pragma optimize("", on)