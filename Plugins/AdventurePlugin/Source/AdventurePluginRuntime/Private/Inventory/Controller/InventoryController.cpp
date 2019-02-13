// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryController.h"

#pragma optimize("", off)



void UInventoryController::ShowInventory(UAdventurePluginGameContext* GameContext, UInventory* Inventory)
{
	CurrentGameContext = GameContext;
	UInventory* InventoryToShow = IsValid(Inventory) ? Inventory : DefaultInventory;

	IInventoryPresenterInterface* PresenterInstance = GetPresenter();
	if (PresenterInstance && IsValid(GameContext))
	{
		IInventoryPresenterInterface::Execute_ShowInventory(PresenterInstance->_getUObject(), InventoryToShow, GameContext->InventoryController);
	}
	else
	{
		//TODO: Log Error.
	}
}

UInventory* UInventoryController::GetInventory()
{
	return DefaultInventory;
}

void UInventoryController::HideInventory()
{
	IInventoryPresenterInterface* PresenterInstance = GetPresenter();
	if (PresenterInstance && IsValid(CurrentGameContext))
	{
		IInventoryPresenterInterface::Execute_HideInventory(PresenterInstance->_getUObject(), CurrentGameContext->InventoryController);
	}
	else
	{
		//TODO: Log error
	}

	CurrentGameContext = nullptr;
}

#pragma optimize("", on)