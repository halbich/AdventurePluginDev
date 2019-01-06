// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginCombinationsBlueprintLibrary.h"

#pragma optimize("", off)
USimpleCombination* UAdventurePluginCombinationsBlueprintLibrary::CreateSimpleCombination(TSubclassOf<UCombinableObject> TargetObject, FText CombinationName, FCombinationEvent CombinationEvent) {
	auto* combination = NewObject<USimpleCombination>();
	combination->Name = CombinationName;
	combination->CombinationEvent = CombinationEvent;
	combination->TargetClass = TargetObject;
	return combination;
}

#pragma optimize("", on)