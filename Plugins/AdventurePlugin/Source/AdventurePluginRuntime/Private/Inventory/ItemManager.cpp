#include "ItemManager.h"
#include "AdventurePluginRuntime.h"

#pragma optimize("", off)
UInventoryItem* UItemManager::GetItem(TSubclassOf<UInventoryItem> Item)
{
	if (Item == nullptr)
	{
		LOG_Warning(NSLOCTEXT("AP", "getItemNull", "ItemManager::GetItem - Item is NULL."));
		return nullptr;
	}
	if (Item->HasAnyClassFlags(CLASS_Abstract))
	{
		LOG_Warning(NSLOCTEXT("AP", "getItemAbstract", "ItemManager::GetItem - Item is abstract."));
		return nullptr;
	}
	auto* toReturn = Items.Find(Item);
	if (toReturn == nullptr || *toReturn == nullptr || !(*toReturn)->IsValidLowLevel())
	{
		RegisterItem(Item);
		toReturn = Items.Find(Item);
	}
	check(toReturn && *toReturn && "Item instance should never be null");
	return toReturn ? *toReturn : nullptr;
}

void UItemManager::RegisterItem(TSubclassOf<UInventoryItem> ItemClass)
{
	UInventoryItem* newItem = NewObject<UInventoryItem>(this, ItemClass);
	newItem->Init();
	check(newItem != nullptr && "It should always be possible to instantiate an inventory item");
	Items.Add(ItemClass, newItem);
}
#pragma optimize("", on)