#include "InventoryItem.h"
#include "AdventurePluginGameContext.h"
#include "ItemManager.h"
#include "InventoryItemBlueprint.h"
#include "AdventurePluginRuntime.h"

#pragma optimize("", off)
void UInventoryItem::InitCombinations_Implementation() {

}
void UInventoryItem::CheckIsInitializingCombinations()
{
	if (!IsInitializingCombinations)
	{
		LOG_Warning(NSLOCTEXT("AP", "Combinations not initializing", "Combinations should not be added to an item outside of InitCombinations method"));
	}
}
void UInventoryItem::RefreshCombinations()
{
	IsInitializingCombinations = true;
	Combinations.Empty();
	InitCombinations();
	IsInitializingCombinations = false;
#if WITH_EDITORONLY_DATA
	AllCombinations.Empty();
	for (auto entry : Combinations)
	{
		auto currentCombination = entry.Value;
		if (!currentCombination)
		{
			continue;
		}
		auto allCombinationTargets = currentCombination->Execute_GetCombinationTargetClasses(currentCombination.GetObject());
		for (auto* combinationTarget : allCombinationTargets)
		{
			if (!combinationTarget)
			{
				continue;
			}
			auto* targetClassBlueprint = combinationTarget ? combinationTarget->ClassGeneratedBy : nullptr;
			if (targetClassBlueprint == nullptr || !targetClassBlueprint->IsValidLowLevel())
			{
				continue;
			}
			UBlueprint* targetClassBlueprintCasted = Cast<UBlueprint>(targetClassBlueprint);
			AllCombinations.Add(targetClassBlueprintCasted, entry.Value);
		}
	}
#endif
}

void UInventoryItem::AddCombinationObject(TSubclassOf<UInventoryItem> InventoryItem, UItemCombination* ToAdd)
{
	Combinations.Add(InventoryItem, ToAdd);
}

void UInventoryItem::AddCombination(TSubclassOf<UInventoryItem> InventoryItem, FText CombinationName, FCombinationEvent CombinationEvent)
{
	auto* combination = NewObject<UItemCombination>();
	combination->Name = CombinationName;
	combination->CombinationEvent = CombinationEvent;
	combination->TargetClass = InventoryItem;
	Combinations.Add(InventoryItem, combination);
}

bool UInventoryItem::TryCombineWith(UInventoryItem* TargetItem, UAdventurePluginGameContext* Context)
{
	if (TargetItem == nullptr || !TargetItem->IsValidLowLevel())
	{ 
		LOG_Warning(NSLOCTEXT("AP", "NullCombinationItem", "One of the items being combined is null."));
		return false;
	}
	// Try to find a combination on this item
	if (TryCombineWithInternal(TargetItem, Context))
	{
		return true;
	} 
	// Try to find a combination on the target item.
	return TargetItem->TryCombineWithInternal(this, Context);
}
bool UInventoryItem::TryCombineWithInternal(UInventoryItem* TargetItem, UAdventurePluginGameContext* Context)
{
	auto* combination = Combinations.Find(TargetItem->GetClass());
	if (combination == nullptr || *combination == nullptr)
	{
		return false;
	}
	auto* combinationObject = combination->GetObject();
	(*combination)->Execute_Execute(combinationObject, TargetItem, Context);
	return true;
}
#pragma optimize("", on)