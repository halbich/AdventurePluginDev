#include "InventoryItem.h"
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

bool UInventoryItem::TryCombineWith(UClass* TargetItem, UAdventurePluginGameContext* Context)
{
	// Try to find a combination on this item
	if (TryCombineWithInternal(TargetItem, Context))
	{
		return true;
	} 
	//HACK: Access global version of this class
	auto* targetItem = NewObject<UInventoryItem>(this, TargetItem);
	// Try to find a combination on the target item.
	return targetItem->TryCombineWithInternal(this->GetClass(), Context);
}
bool UInventoryItem::TryCombineWithInternal(UClass* TargetItem, UAdventurePluginGameContext* Context)
{
	// HACK: Refresh should be done on init
	RefreshCombinations();
	auto* combination = Combinations.Find(TargetItem);
	if (combination == nullptr || *combination == nullptr)
	{
		return false;
	}
	// HACK: We should access some global instance of this class
	auto* targetItem = NewObject<UInventoryItem>(this, TargetItem);
	(*combination)->CombinationEvent.Execute(targetItem, Context);
	return true;
}
#pragma optimize("", on)