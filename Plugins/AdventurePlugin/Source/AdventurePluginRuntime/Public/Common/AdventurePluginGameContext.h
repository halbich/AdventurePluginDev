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

	UPROPERTY(BlueprintReadOnly, Transient)
		UInventoryController* InventoryController;

	UPROPERTY(BlueprintReadOnly, Transient)
		TScriptInterface< IInventoryPresenterInterface> InventoryPresenter;

	UPROPERTY(BlueprintReadOnly, Transient)
		UDialogController* DialogController;

	UPROPERTY(BlueprintReadOnly, Transient)
		TScriptInterface< IDialogPresenterInterface> DialogPresenter;

	UPROPERTY(BlueprintReadWrite, Transient, Category="Adventure Plugin | Game Context")
		UAdventurePluginSaveGame* SaveGame;

		UPROPERTY(BlueprintReadOnly, Transient)
		UItemManager* ItemManager;

	UPROPERTY(BlueprintReadOnly, Transient)
		UAdventureCharacterManager* AdventureCharacterManager;

};
