// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AdventurePluginGameContext.generated.h"

class UInventoryController;
class IInventoryPresenterInterface;

class UDialogueController;
class IDialoguePresenterInterface;

class UAdventurePluginSaveGame;

/**
 *
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginGameContext : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Transient)
		UInventoryController* InventoryController;

	UPROPERTY(BlueprintReadOnly, Transient)
		TScriptInterface< IInventoryPresenterInterface> InventoryPresenter;

	UPROPERTY(BlueprintReadOnly, Transient)
		UDialogueController* DialogueController;

	UPROPERTY(BlueprintReadOnly, Transient)
		TScriptInterface< IDialoguePresenterInterface> DialoguePresenter;

	UPROPERTY(BlueprintReadOnly, Transient)
		UAdventurePluginSaveGame* SaveGame;
};
