// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/Manager/InventoryController.h"

#pragma optimize("", off)

void UInventoryController::SetGameInstance(UGameInstance* instance)
{
	if (!instance || !instance->IsValidLowLevel()) return;
	cachedGameInstance = instance;
}

void UInventoryController::ShowInventory(UInventory* inventory)
{
	ensurePresenterInstance();

	auto world = cachedGameInstance->GetWorld();
	auto controller = UGameplayStatics::GetPlayerController(world, 0);
	
	/* TODO *
	FInputModeGameAndUI Mode;
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	controller->SetInputMode(Mode);
	controller->bShowMouseCursor = true;
	/**/

	auto inv = (inventory && inventory->IsValidLowLevel()) ? inventory : defaultInventory;
	presenterInstance->Execute_ShowInventory(presenterInstance->_getUObject(), inv, this);
	presenterInstance->AddToViewport(0);
}

UInventory* UInventoryController::GetInventory()
{
	return defaultInventory;
}

void UInventoryController::HideInventory()
{
	ensurePresenterInstance();

	presenterInstance->Execute_HideInventory(presenterInstance->_getUObject(), this);
	presenterInstance->RemoveFromViewport();

	auto world = cachedGameInstance->GetWorld();
	auto controller = UGameplayStatics::GetPlayerController(world, 0);

	/* TODO *
	FInputModeGameOnly Mode;
	controller->SetInputMode(Mode);
	controller->bShowMouseCursor = false;
	/**/
}

#pragma optimize("", on)