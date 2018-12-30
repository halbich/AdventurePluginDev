#include "InventoryItem.h"
#include "AdventurePluginGameContext.h"
#include "ItemManager.h"
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
}

void UInventoryItem::AddCombinationObject(UClass* InventoryItem, UItemCombination* ToAdd)
{
	Combinations.Add(InventoryItem, ToAdd);
}

void UInventoryItem::AddCombination(UClass* InventoryItem, FText CombinationName, FCombinationEvent CombinationEvent)
{
	auto* combination = NewObject<UItemCombination>();
	combination->Name = CombinationName;
	combination->CombinationEvent = CombinationEvent;
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
	(*combination)->CombinationEvent.Execute(TargetItem, Context);
	return true;
}
#pragma optimize("", on)