// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryController.h"

#pragma optimize("", off)



void UInventoryController::ShowInventory(UAdventurePluginGameContext* gameContext, UInventory* inventory)
{
	currentContext = gameContext;
	auto inv = (inventory && inventory->IsValidLowLevel()) ? inventory : defaultInventory;

	auto presenterInstance = presenter();
	if (presenterInstance)
		IInventoryPresenterInterface::Execute_ShowInventory(presenterInstance->_getUObject(), inv, currentContext->InventoryController);
}

UInventory* UInventoryController::GetInventory()
{
	return defaultInventory;
}

void UInventoryController::HideInventory()
{
	auto presenterInstance = presenter();
	if (presenterInstance)
		IInventoryPresenterInterface::Execute_HideInventory(presenterInstance->_getUObject(), currentContext->InventoryController);

	currentContext = NULL;
}

#pragma optimize("", on)