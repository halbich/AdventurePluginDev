// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginCombinationsBlueprintLibrary.h"

#pragma optimize("", off)
UGenericCombinationWithSingleItem* UAdventurePluginCombinationsBlueprintLibrary::CreateGenericCombinationWithSingleItem(TSubclassOf<UCombinableObject> TargetObject, FText CombinationName, FCombinationEvent CombinationEvent)
{
	UGenericCombinationWithSingleItem* NewCombination = NewObject<UGenericCombinationWithSingleItem>();
	NewCombination->Name = CombinationName;
	NewCombination->CombinationEvent = CombinationEvent;
	NewCombination->TargetClass = TargetObject;
	return NewCombination;
}

USimpleCombinationWithSingleItem* UAdventurePluginCombinationsBlueprintLibrary::CreateSimpleCombinationWithSingleItem(TSubclassOf<UCombinableObject> TargetObject, TSubclassOf<UInventoryItem> ResultItem, FText CombinationName)
{
	USimpleCombinationWithSingleItem* NewCombination = NewObject<USimpleCombinationWithSingleItem>();
	NewCombination->Name = CombinationName;
	NewCombination->TargetClass = TargetObject;
	NewCombination->ResultItemClass = ResultItem;
	return NewCombination;
}

#pragma optimize("", on)