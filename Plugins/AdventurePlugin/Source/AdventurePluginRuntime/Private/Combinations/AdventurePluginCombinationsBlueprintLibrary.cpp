// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginCombinationsBlueprintLibrary.h"

#pragma optimize("", off)
UItemCombination* UAdventurePluginCombinationsBlueprintLibrary::CreateSimpleCombination(TSubclassOf<UCombinableObject> TargetObject, FText CombinationName, FCombinationEvent CombinationEvent) {
	auto* combination = NewObject<UItemCombination>();
	combination->Name = CombinationName;
	combination->CombinationEvent = CombinationEvent;
	combination->TargetClass = TargetObject;
	return combination;
}

#pragma optimize("", on)