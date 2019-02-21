// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryController.h"

void UInventoryController::ShowInventory(UAdventurePluginGameContext* GameContext, UInventory* Inventory)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("InventoryController:ShowInventory")))
	{
		return;
	}
	UInventory* InventoryToShow = IsValid(Inventory) ? Inventory : DefaultInventory;
	IInventoryPresenterInterface::Execute_ShowInventory(GameContext->InventoryPresenter.GetObject(), InventoryToShow, GameContext);
}

UInventory* UInventoryController::GetInventory()
{
	return DefaultInventory;
}

void UInventoryController::HideInventory(UAdventurePluginGameContext* GameContext, UInventory* Inventory)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("InventoryController:HideInventory")))
	{
		return;
	}
	UInventory* InventoryToHide = IsValid(Inventory) ? Inventory : DefaultInventory;
	IInventoryPresenterInterface::Execute_HideInventory(GameContext->InventoryPresenter.GetObject(), InventoryToHide, GameContext);
}