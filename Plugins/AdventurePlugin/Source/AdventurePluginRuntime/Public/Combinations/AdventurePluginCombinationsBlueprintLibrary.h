// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CombinableObject.h"
#include "InventoryItem.h"
#include "SimpleCombinationWithSingleItem.h"
#include "GenericCombinationWithSingleItem.h"
#include "UseActionType.h"
#include "AdventurePluginCombinationsBlueprintLibrary.generated.h"

/**
* This library defines static functions regarding combinations.
*/
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginCombinationsBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*Create a simple combination that represents combination with one single object, with specific constant combination name and that executes a specified event when Execute is called.*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Combinations")
		static UGenericCombinationWithSingleItem* CreateGenericCombinationWithSingleItem(TSubclassOf<UCombinableObject> TargetObject, FText CombinationName, FUseActionType CombinationType, FCombinationEvent CombinationEvent);
	/*Create a simple combination that represents combination with one single object, with specific constant combination name and that, upon execute, creates a specified object in inventory and removes the combined items from inventory if possible.*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Combinations")
		static USimpleCombinationWithSingleItem* CreateSimpleCombinationWithSingleItem(TSubclassOf<UCombinableObject> TargetObject, TSubclassOf<UInventoryItem> ResultItem, FText CombinationName, FUseActionType CombinationType);

private:
};
