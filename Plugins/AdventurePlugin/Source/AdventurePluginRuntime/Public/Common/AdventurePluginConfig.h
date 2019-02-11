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
 *
 */
UCLASS(Config = AdventurePlugin, DefaultConfig)
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginConfig : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(Config, EditAnywhere, Category = Dialog, DisplayName = "Default Presenter")
		TSoftClassPtr<UDialogPresenterWidget> DefaultDialogPresenterWidget;

	UPROPERTY(Config, EditAnywhere, Category = Dialog, DisplayName = "Default Controller")
		TSoftClassPtr<UDialogController> DefaultDialogController;

	UPROPERTY(Config, EditAnywhere, Category = Inventory, DisplayName = "Default Presenter")
		TSoftClassPtr<UInventoryPresenterWidget> DefaultInventoryPresenterWidget;

	UPROPERTY(Config, EditAnywhere, Category = Inventory, DisplayName = "Default Controller")
		TSoftClassPtr<UInventoryController> DefaultInventoryController;

	UPROPERTY(Config, EditAnywhere, Category = Inventory, DisplayName = "Default Item Manager")
		TSoftClassPtr<UItemManager> DefaultItemManager;

	UPROPERTY(Config, EditAnywhere, Category = Dialog, DisplayName = "Default Adventure Character Manager")
		TSoftClassPtr<UAdventureCharacterManager> DefaultAdventureCharacterManager;
	/* Defines the actual actions that can be represented by the Use action. E.g. Using a talking sword might be Talk action, using a mechanism might also be a different action etc. Mainly for determining the Use action icon.*/
	UPROPERTY(Config, EditAnywhere, Category = Inventory, DisplayName = "Supported item tags")
		TSet<FName> UseActionTypes;
};
