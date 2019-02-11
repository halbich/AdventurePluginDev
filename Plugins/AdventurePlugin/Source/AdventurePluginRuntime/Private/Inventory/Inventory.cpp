#include "Inventory.h"

bool UInventory::HasItem(UInventoryItem* Item)
{
	return Items.Contains(Item);
}

bool UInventory::AddItem(UInventoryItem* Item)
{
	if (Items.Contains(Item))
	{
		return false;
	}
	Items.Add(Item);
	// TODO: Item state: Should we do it here? Or should presenter be responsible
	Item->ItemState = EInventoryItemState::ItemState_InInventory;
	if (!bIsUpdating)
	{
		InventoryChanged.Broadcast(Item);
	}
	return true;
}

bool UInventory::RemoveItem(UInventoryItem* Item)
{
	if (!Items.Contains(Item)) return false;
	Items.Remove(Item);
	// TODO: Item state: Should we do it here? Or should presenter be responsible
	Item->ItemState = EInventoryItemState::ItemState_Used;
	if (!bIsUpdating)
	{
		InventoryChanged.Broadcast(Item);
	}
	return true;
}

void UInventory::BeginUpdate()
{
	bIsUpdating = true;
}

void UInventory::EndUpdate()
{
	if (bIsUpdating)
	{
		// TODO: Store changed items and broadcast also the list of modified items.
		InventoryChanged.Broadcast(nullptr);
	}
	bIsUpdating = false;
}