// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginCombinationsBlueprintLibrary.h"

#pragma optimize("", off)
USimpleCombination* UAdventurePluginCombinationsBlueprintLibrary::CreateSimpleCombination(TSubclassOf<UCombinableObject> TargetObject, FText CombinationName, FCombinationEvent CombinationEvent) {
	USimpleCombination* NewCombination = NewObject<USimpleCombination>();
	NewCombination->Name = CombinationName;
	NewCombination->CombinationEvent = CombinationEvent;
	NewCombination->TargetClass = TargetObject;
	return NewCombination;
}

#pragma optimize("", on)