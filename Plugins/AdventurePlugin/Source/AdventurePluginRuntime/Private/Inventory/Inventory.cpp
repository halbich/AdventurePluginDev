#include "Inventory.h"

bool UInventory::HasItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContext)
{
	return Items.Contains(Item);
}

bool UInventory::AddItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContext)
{
	if (Items.Contains(Item))
	{
		return false;
	}
	Items.Add(Item);
	// TODO: Item state: Should we do it here? Or should presenter be responsible
	Item->SetItemState(EInventoryItemState::ItemState_InInventory, GameContext);
	if (!bIsUpdating)
	{
		InventoryChanged.Broadcast(Item);
	}
	Item->OnAddedToInventory.Broadcast(Item);
	return true;
}

bool UInventory::RemoveItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContext)
{
	if (!Items.Contains(Item)) return false;
	Items.Remove(Item);
	// TODO: Item state: Should we do it here? Or should presenter be responsible
	Item->SetItemState(EInventoryItemState::ItemState_Used, GameContext);
	if (!bIsUpdating)
	{
		InventoryChanged.Broadcast(Item);
	}
	Item->OnRemovedFromInventory.Broadcast(Item);
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