#include "Inventory.h"

bool UInventory::HasItem(UInventoryItem* item)
{
	return Items.Contains(item);
}

bool UInventory::AddItem(UInventoryItem* item)
{
	if (Items.Contains(item)) return false;
	Items.Add(item);
	if (!isUpdating)
	{
		InventoryChanged.Broadcast(item);
	}
	return true;
}

bool UInventory::RemoveItem(UInventoryItem* item)
{
	if (!Items.Contains(item)) return false;
	Items.Remove(item);
	if (!isUpdating)
	{
		InventoryChanged.Broadcast(item);
	}
	return true;
}

void UInventory::BeginUpdate()
{
	isUpdating = true;
}

void UInventory::EndUpdate()
{
	if (isUpdating)
	{
		// TODO: Store changed items and broadcast also the list of modified items.
		InventoryChanged.Broadcast(nullptr);
	}
	isUpdating = false;
}