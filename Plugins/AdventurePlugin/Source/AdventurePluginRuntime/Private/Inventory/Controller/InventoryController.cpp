// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryController.h"

void UInventoryController::ShowInventory(UAdventurePluginGameContext* GameContext, UInventory* Inventory)
{
	CurrentGameContext = GameContext;
	UInventory* InventoryToShow = IsValid(Inventory) ? Inventory : DefaultInventory;

	TScriptInterface<IInventoryPresenterInterface> PresenterInstance = GetPresenter();
	if (PresenterInstance && UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("InventoryController:ShowInventory")))
	{
		IInventoryPresenterInterface::Execute_ShowInventory(PresenterInstance.GetObject(), InventoryToShow, GameContext->InventoryController);
	}
}

UInventory* UInventoryController::GetInventory()
{
	return DefaultInventory;
}

void UInventoryController::HideInventory()
{
	TScriptInterface<IInventoryPresenterInterface> PresenterInstance = GetPresenter();
	if (PresenterInstance && UAdventurePluginGameContext::IsGameContextValid(CurrentGameContext, TEXT("InventoryController:HideInventory")))
	{
		IInventoryPresenterInterface::Execute_HideInventory(PresenterInstance.GetObject(), CurrentGameContext->InventoryController);
	}

	CurrentGameContext = nullptr;
}
TScriptInterface<IInventoryPresenterInterface> UInventoryController::GetPresenter()
{
	if (!UAdventurePluginGameContext::IsGameContextValid(CurrentGameContext, TEXT("InventoryController:GetPresenter")))
	{
		return nullptr;
	}
	if (!IsValid(CurrentGameContext->InventoryPresenter.GetObject()))
	{
		LOG_Error(NSLOCTEXT("AP", "InventoryControllerPresenterNull", "InventoryController:GetPresenter: Inventory presenter is null or invalid."));
		return nullptr;
	}
	return CurrentGameContext->InventoryPresenter;
}