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

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Inventory")
	UInventoryController* InventoryController;

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Inventory")
	TScriptInterface< IInventoryPresenterInterface> InventoryPresenter;

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Dialog")
	UDialogController* DialogController;

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Dialog")
	TScriptInterface< IDialogPresenterInterface> DialogPresenter;

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Game Context")
	UAdventurePluginSaveGame* SaveGame;

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Inventory")
	UItemManager* ItemManager;

	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Character")
	UAdventureCharacterManager* AdventureCharacterManager;
	/*Returns true if the game context and all of its direct subclasses are true. If not, it will log an error, which will include caller as a description of where this problem happened.*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin")
	static bool IsGameContextValid(const UAdventurePluginGameContext* GameContext, const FString& Caller);
};
