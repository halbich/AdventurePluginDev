#include "Inventory.h"

bool UInventory::HasItem(UInventoryItem* item)
{
	return Items.Contains(item);
}

bool UInventory::AddItem(UInventoryItem* item)
{
	if (Items.Contains(item)) return false;
	Items.Add(item);
	return true;
}

bool UInventory::RemoveItem(UInventoryItem* item)
{
	if (!Items.Contains(item)) return false;
	Items.Remove(item);
	return true;
}


bool UInventory::RemoveItemWithClass(UClass* item)
{
	for (auto* itemInstance : Items) 
	{
		if (itemInstance && itemInstance->IsA(item))
		{
			return RemoveItem(itemInstance);
		}
	}
	return false;
}