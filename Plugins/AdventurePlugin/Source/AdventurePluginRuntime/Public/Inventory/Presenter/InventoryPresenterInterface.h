// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UniquePtr.h"
#include "Inventory/Inventory.h"
#include "InventoryPresenterInterface.generated.h"

class UInventoryController;

/**
 * @see IInventoryPresenterInterface
 */
UINTERFACE(BlueprintType)
class ADVENTUREPLUGINRUNTIME_API UInventoryPresenterInterface : public UInterface
{
	GENERATED_BODY()


};
/**
* An interface that must be implemented by all inventory presenters, that is classes which can show or hide an inventory.
* The presenter should also be responsible for calling the appropriate item functions when user uses items, combines items etc.
*/
class ADVENTUREPLUGINRUNTIME_API IInventoryPresenterInterface
{
	GENERATED_BODY()

public:
	/**
	* Displays the specified inventory to the player.
	* @param Inventory The inventory to present.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Inventory")
		void ShowInventory(UInventory* Inventory, UAdventurePluginGameContext* GameContext);
	/**
	* Hides the currently shown inventory.
	* @param Inventory The inventory to hide.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Inventory")
		void HideInventory(UInventory* Inventory, UAdventurePluginGameContext* GameContext);
};
