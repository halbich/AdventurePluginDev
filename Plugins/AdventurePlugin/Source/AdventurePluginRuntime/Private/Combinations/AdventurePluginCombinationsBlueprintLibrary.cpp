#include "Combinations/AdventurePluginCombinationsBlueprintLibrary.h"

UGenericCombinationWithSingleItem* UAdventurePluginCombinationsBlueprintLibrary::CreateGenericCombinationWithSingleItem(TSubclassOf<UCombinableObject> TargetObject, FText CombinationName, FUseActionType CombinationType, FCombinationEvent CombinationEvent)
{
	UGenericCombinationWithSingleItem* NewCombination = NewObject<UGenericCombinationWithSingleItem>();
	NewCombination->Name = CombinationName;
	NewCombination->CombinationEvent = CombinationEvent;
	NewCombination->TargetClass = TargetObject;
	NewCombination->ActionType = CombinationType;
	return NewCombination;
}

USimpleCombinationWithSingleItem* UAdventurePluginCombinationsBlueprintLibrary::CreateSimpleCombinationWithSingleItem(TSubclassOf<UCombinableObject> TargetObject, TSubclassOf<UInventoryItem> ResultItem, FText CombinationName, FUseActionType CombinationType)
{
	USimpleCombinationWithSingleItem* NewCombination = NewObject<USimpleCombinationWithSingleItem>();
	NewCombination->Name = CombinationName;
	NewCombination->TargetClass = TargetObject;
	NewCombination->ResultItemClass = ResultItem;
	NewCombination->ActionType = CombinationType;
	return NewCombination;
}

UStartDialogCombinationWithSingleItem* UAdventurePluginCombinationsBlueprintLibrary::CreateDialogCombinationWithSingleItem(TSubclassOf<UCombinableObject> TargetObject, FDialogGraphEntryPoint DialogToStart, FText CombinationName, FUseActionType CombinationType)
{
	UStartDialogCombinationWithSingleItem* NewCombination = NewObject<UStartDialogCombinationWithSingleItem>();
	NewCombination->Name = CombinationName;
	NewCombination->TargetClass = TargetObject;
	NewCombination->DialogToStart = DialogToStart;
	NewCombination->ActionType = CombinationType;
	return NewCombination;
}
