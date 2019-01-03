// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CombinableObject.h"
#include "ItemCombination.h"
#include "AdventurePluginCombinationsBlueprintLibrary.generated.h"

/**
*
*/
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginCombinationsBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Combinations")
		static UItemCombination* CreateSimpleCombination(TSubclassOf<UCombinableObject> TargetObject, FText CombinationName, FCombinationEvent CombinationEvent);

private:
};
