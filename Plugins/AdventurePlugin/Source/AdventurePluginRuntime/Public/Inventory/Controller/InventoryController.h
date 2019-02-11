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
 *
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

	void ShowInventory(UAdventurePluginGameContext* GameContext, UInventory* Inventory = nullptr);

	void HideInventory();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	UInventory* GetInventory();


private:

	UPROPERTY(Transient)
	UInventory* DefaultInventory;

	UPROPERTY(Transient)
		UAdventurePluginGameContext* CurrentGameContext;

	UPROPERTY(Transient)
		TScriptInterface<IInventoryPresenterInterface> CurrentPresenter;

	FORCEINLINE IInventoryPresenterInterface* GetPresenter()
	{
		return IsValid(CurrentGameContext) ? Cast<IInventoryPresenterInterface>(CurrentGameContext->InventoryPresenter.GetObject()) : nullptr;
	}
};
