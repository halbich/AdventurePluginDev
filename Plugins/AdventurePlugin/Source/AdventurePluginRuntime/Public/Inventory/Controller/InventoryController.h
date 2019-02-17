// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "Common/AdventurePluginGameContext.h"
#include "Presenter/InventoryPresenterInterface.h"
#include "Common/AdventurePluginConfig.h"
#include "Kismet/GameplayStatics.h"
#include "InventoryController.generated.h"

/**
 * The class responsible for managing the player's inventory.
 * While this class currently manages only main character's inventory, it could be easily extended to contain other things.
 * For example inventory of other characters or of some chests on the map.
 * It contains all of the data and can also tell the inventory presenter to either show or hide itself.
 */
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UInventoryController : public UObject
{
	GENERATED_BODY()

public:

	UInventoryController()
	{
		DefaultInventory = NewObject<UInventory>();
	}
	/**
	* Tells the presenter to show the specified inventory, or the default inventory if no inventory is specified.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param Inventory The inventory to show. Defaults to null, which means showing the default inventory.
	*/
	void ShowInventory(UAdventurePluginGameContext* GameContext, UInventory* Inventory = nullptr);
	/**
	* If an inventory is being shown, hide it.
	*/
	void HideInventory();
	/**
	* Retrieves the default inventory, belonging to the main player character.
	* @return The default inventory.
	*/
	UFUNCTION(BlueprintCallable, Category="Adventure Plugin|Inventory")
	UInventory* GetInventory();


private:
	/*
	* The default inventory, probably that of the main player character.
	*/
	UPROPERTY(Transient)
	UInventory* DefaultInventory;
	/**
	* Set if displaying an inventory, contains the game context used to show that inventory.
	*/
	UPROPERTY(Transient)
		UAdventurePluginGameContext* CurrentGameContext;
	/**
	* If displaying an inventory, this contains the presenter used to show that inventory.
	*/
	UPROPERTY(Transient)
		TScriptInterface<IInventoryPresenterInterface> CurrentPresenter;
	/**
	* Retrieves the presenter instance used for showing or displaying manuals. 
	* Retrieved from current game context, @see UInventoryController#CurrentGameContext.
	* @return The presenter used to display the inventory.
	*/
	TScriptInterface<IInventoryPresenterInterface> GetPresenter();
};
