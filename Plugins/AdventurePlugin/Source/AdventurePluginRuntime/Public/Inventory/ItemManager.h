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

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
		UInventoryItem* GetItem(TSubclassOf<UInventoryItem> Item)
	{
		return Cast<UInventoryItem>(GetCombinableObjectInstance(Item));
	}
	/*TODO: When Saving game works, this class should be responsible for serializing and deserializing the states of all items.*/
};
