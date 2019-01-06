// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CombinableObject.h"
#include "SimpleCombination.h"
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
		static USimpleCombination* CreateSimpleCombination(TSubclassOf<UCombinableObject> TargetObject, FText CombinationName, FCombinationEvent CombinationEvent);

private:
};
