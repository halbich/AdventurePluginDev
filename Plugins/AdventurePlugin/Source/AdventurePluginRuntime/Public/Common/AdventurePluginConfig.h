// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AdventurePluginConfig.generated.h"

class UDialogPresenterWidget;
class UDialogController;
class UInventoryPresenterWidget;
class UInventoryController;
class UItemManager;
class UAdventureCharacterManager;

/**
 * Contains the configuration for the Adventure Plugin.
 */
UCLASS(Config = AdventurePlugin, DefaultConfig)
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginConfig : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/**
	* Class specifying the dialog presenter widget to be used in the default GameContext. @see UAdventurePluginGameContext
	*/
	UPROPERTY(Config, EditAnywhere, Category = Dialog, DisplayName = "Default Presenter")
	TSoftClassPtr<UDialogPresenterWidget> DefaultDialogPresenterWidget;
	/**
	* Class specifying the dialog controller to be used in the default GameContext. @see UAdventurePluginGameContext
	*/
	UPROPERTY(Config, EditAnywhere, Category = Dialog, DisplayName = "Default Controller")
	TSoftClassPtr<UDialogController> DefaultDialogController;
	/**
	* Class specifying the inventory presenter widget to be used in the default GameContext. @see UAdventurePluginGameContext
	*/
	UPROPERTY(Config, EditAnywhere, Category = Inventory, DisplayName = "Default Presenter")
	TSoftClassPtr<UInventoryPresenterWidget> DefaultInventoryPresenterWidget;
	/**
	* Class specifying the inventory controller to be used in the default GameContext. @see UAdventurePluginGameContext
	*/
	UPROPERTY(Config, EditAnywhere, Category = Inventory, DisplayName = "Default Controller")
	TSoftClassPtr<UInventoryController> DefaultInventoryController;
	/**
	* Class specifying the item manager to be used in the default GameContext. @see UAdventurePluginGameContext
	*/
	UPROPERTY(Config, EditAnywhere, Category = Inventory, DisplayName = "Default Item Manager")
	TSoftClassPtr<UItemManager> DefaultItemManager;
	/**
	* Class specifying the character manager to be used in the default GameContext. @see UAdventurePluginGameContext
	*/
	UPROPERTY(Config, EditAnywhere, Category = Dialog, DisplayName = "Default Adventure Character Manager")
	TSoftClassPtr<UAdventureCharacterManager> DefaultAdventureCharacterManager;
	/**
	* Defines the actions that can be represented by the Use action. 
	* E.g. Using a talking sword might be Talk action, using a mechanism might also be a different action etc.
	* Not doing anything by default, expected use case is determining which icon to use for the use action.*/
	UPROPERTY(Config, EditAnywhere, Category = Inventory, DisplayName = "Use Action types")
	TSet<FName> UseActionTypes;
};
