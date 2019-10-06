#include "Combinations/AdventurePluginCombinationsBlueprintLibrary.h"
#include "Combinations/Combination.h"
#include "Combinations/Triggers/SingleObjectCombinationTrigger.h"
#include "Combinations/Actions/GenericCombinationAction.h"
#include "Combinations/Actions/CombineIntoOneItemCombinationAction.h"
#include "Combinations/Actions/StartDialogCombinationAction.h"

UCombination* UAdventurePluginCombinationsBlueprintLibrary::CreateGenericCombinationWithSingleItem(TSubclassOf<UCombinableObject> TargetObject, FText CombinationName, FUseActionType CombinationType, FCombinationEvent CombinationEvent)
{
	UCombination* NewCombination = NewObject<UCombination>();
	NewCombination->Name = CombinationName;
	NewCombination->ActionType = CombinationType;

	auto* action = NewObject<UGenericCombinationAction>();
	action->CombinationEvent = CombinationEvent;
	NewCombination->CombinationAction = action;

	auto* trigger = NewObject<USingleObjectCombinationTrigger>();
	trigger->TargetClass = TargetObject;
	NewCombination->CombinationTrigger = trigger;

	return NewCombination;
}

UCombination* UAdventurePluginCombinationsBlueprintLibrary::CreateSimpleCombinationWithSingleItem(TSubclassOf<UCombinableObject> TargetObject, TSubclassOf<UInventoryItem> ResultItem, FText CombinationName, FUseActionType CombinationType)
{
	UCombination* NewCombination = NewObject<UCombination>();
	NewCombination->Name = CombinationName;
	NewCombination->ActionType = CombinationType;

	auto* action = NewObject<UCombineIntoOneItemCombinationAction>();
	action->ResultItemClass = ResultItem;
	NewCombination->CombinationAction = action;

	auto* trigger = NewObject<USingleObjectCombinationTrigger>();
	trigger->TargetClass = TargetObject;
	NewCombination->CombinationTrigger = trigger;

	return NewCombination;
}

UCombination* UAdventurePluginCombinationsBlueprintLibrary::CreateDialogCombinationWithSingleItem(TSubclassOf<UCombinableObject> TargetObject, FDialogGraphEntryPoint DialogToStart, FText CombinationName, FUseActionType CombinationType)
{
	UCombination* NewCombination = NewObject<UCombination>();
	NewCombination->Name = CombinationName;
	NewCombination->ActionType = CombinationType;

	auto* action = NewObject<UStartDialogCombinationAction>();
	action->DialogToStart = DialogToStart;
	NewCombination->CombinationAction = action;

	auto* trigger = NewObject<USingleObjectCombinationTrigger>();
	trigger->TargetClass = TargetObject;
	NewCombination->CombinationTrigger = trigger;

	return NewCombination;
}
