// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "Common/AdventurePluginGameContext.h"
#include "Combinations/CombinableObjectManager.h"
#include "InventoryItem.h"
#include "ItemManager.generated.h"

/**
*
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UItemManager : public UCombinableObjectManager
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		UInventoryItem* GetItem(TSubclassOf<UInventoryItem> Item)
	{
		return Cast<UInventoryItem>(GetObject(Item));
	}
};
