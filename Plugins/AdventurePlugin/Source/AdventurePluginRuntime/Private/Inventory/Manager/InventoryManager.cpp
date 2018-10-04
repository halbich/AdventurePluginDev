// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/Manager/InventoryManager.h"

#pragma optimize("", off)

void UInventoryManager::SetGameInstance(UGameInstance* instance)
{
	if (!instance || !instance->IsValidLowLevel()) return;
	cachedGameInstance = instance;
}

void UInventoryManager::ShowInventory(UInventory* inventory)
{
	ensurePresenterInstance();

	auto world = cachedGameInstance->GetWorld();
	auto controller = UGameplayStatics::GetPlayerController(world, 0);
	
	// TODO
	FInputModeGameAndUI Mode;
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	controller->SetInputMode(Mode);
	controller->bShowMouseCursor = true;

	auto inv = (inventory && inventory->IsValidLowLevel()) ? inventory : defaultInventory;
	presenterInstance->Execute_ShowInventory(presenterInstance->_getUObject(), inv, this);
	presenterInstance->AddToViewport(0);
}

UInventory* UInventoryManager::GetInventory()
{
	return defaultInventory;
}

void UInventoryManager::HideInventory()
{
	ensurePresenterInstance();

	presenterInstance->Execute_HideInventory(presenterInstance->_getUObject(), this);
	presenterInstance->RemoveFromViewport();

	auto world = cachedGameInstance->GetWorld();
	auto controller = UGameplayStatics::GetPlayerController(world, 0);

	// TODO
	FInputModeGameOnly Mode;
	controller->SetInputMode(Mode);
	controller->bShowMouseCursor = false;
}

#pragma optimize("", on)