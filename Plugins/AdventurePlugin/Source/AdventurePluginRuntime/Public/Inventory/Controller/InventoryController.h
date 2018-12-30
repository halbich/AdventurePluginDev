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
		defaultInventory = NewObject<UInventory>();
	}

	void ShowInventory(UAdventurePluginGameContext* gameContext, UInventory* inventory = nullptr);

	void HideInventory();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	UInventory* GetInventory();


private:

	UPROPERTY(Transient)
	UInventory* defaultInventory;

	UPROPERTY(Transient)
		UAdventurePluginGameContext* currentContext;

	UPROPERTY(Transient)
		TScriptInterface<IInventoryPresenterInterface> currentPresenter;

	FORCEINLINE IInventoryPresenterInterface* presenter()
	{
		return currentContext ? Cast<IInventoryPresenterInterface>(currentContext->InventoryPresenter.GetObject()) : NULL;
	}
};
