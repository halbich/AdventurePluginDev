// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "Common/AdventurePluginGameContext.h"
#include "Presenter/InventoryPresenterInterface.h"
#include "Common/AdventurePluginConfig.h"
#include "Kismet/GameplayStatics.h"
#include "ItemManager.generated.h"

/**
*
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UItemManager : public UObject
{
	GENERATED_BODY()

public:

	UItemManager()
	{
		RegisterAllItems();
	}

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		UInventoryItem* GetItem(TSubclassOf<UInventoryItem> Item);


private:

	void RegisterItem(TSubclassOf<UInventoryItem> ItemClass);
	void RegisterAllItems();

	UPROPERTY(Transient)
		TMap<TSubclassOf<UInventoryItem>, UInventoryItem*> Items;
};
