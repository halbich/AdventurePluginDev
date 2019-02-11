// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AdventurePluginGameContext.generated.h"

class UInventoryController;
class IInventoryPresenterInterface;

class UDialogController;
class IDialogPresenterInterface;
class UItemManager;
class UAdventureCharacterManager;

class UAdventurePluginSaveGame;

/**
 *
 */
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginGameContext : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Adventure Plugin|Inventory")
		UInventoryController* InventoryController;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Adventure Plugin|Inventory")
		TScriptInterface< IInventoryPresenterInterface> InventoryPresenter;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Adventure Plugin|Dialog")
		UDialogController* DialogController;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Adventure Plugin|Dialog")
		TScriptInterface< IDialogPresenterInterface> DialogPresenter;

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Game Context")
		UAdventurePluginSaveGame* SaveGame;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Adventure Plugin|Inventory")
		UItemManager* ItemManager;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Adventure Plugin|Character")
		UAdventureCharacterManager* AdventureCharacterManager;

};
