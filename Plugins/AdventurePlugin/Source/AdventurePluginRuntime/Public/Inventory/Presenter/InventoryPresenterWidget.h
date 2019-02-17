// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPresenterInterface.h"
#include "InventoryPresenterWidget.generated.h"



/**
 * Base class for inventory presenter widgets. For details @see IInventoryPresenterInterface
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UInventoryPresenterWidget : public UUserWidget, public IInventoryPresenterInterface
{
	GENERATED_BODY()

public:
	/**
	* Displays the specified inventory to the player.
	* @param Inventory The inventory to present.
	* @param InventoryController The controller managing this inventory.
	*/
	void ShowInventory(UInventory* Inventory, UInventoryController* InventoryController);
	/**
	* Hides the currently shown inventory.
	* @param InventoryController The controller managing the currently shown inventory.
	*/
	void HideInventory(UInventoryController* InventoryController);
};
