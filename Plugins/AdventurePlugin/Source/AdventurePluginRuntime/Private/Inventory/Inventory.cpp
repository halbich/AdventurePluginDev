
#include "Inventory.h"
#include "AdventurePluginSaveGame.h"
#include "AdventurePluginGameContext.h"
#include "ItemManager.h"

bool UInventory::HasItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContext)
{
	return GetItems(GameContext).Contains(Item);
}

bool UInventory::AddItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContext)
{
	// Add an item, change item state and raise all events as necessary.
	TArray<UInventoryItem*> Items = GetItems(GameContext);
	if (!IsValid(Item) || Items.Contains(Item))
	{
		return false;
	}
	Items.Add(Item);
	SetItems(Items, GameContext);
	if (Item->GetItemState(GameContext) != EInventoryItemState::ItemState_Custom)
	{
		// Automatically change item state if the designer is not handling it himself.
		Item->SetItemState(EInventoryItemState::ItemState_InInventory, GameContext);
	}
	if (!bIsUpdating)
	{
		InventoryChanged.Broadcast(TArray<UInventoryItem*> { Item });
	}
	else
	{
		ModifiedItems.Add(Item);
	}
	Item->OnAddedToInventory(this, GameContext);
	// While it might be better for the event to be raised by OnAddedToInventory, that could be easily forgotten by designers overriding that. And we don't want that.
	Item->AddedToInventory.Broadcast(Item);
	return true;
}

bool UInventory::RemoveItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContext)
{
	// Remove item, change item state and raise all events as necessary.
	TArray<UInventoryItem*> Items = GetItems(GameContext);
	if (!IsValid(Item) || !Items.Contains(Item)) 
	{
		return false;
	}
	Items.Remove(Item);
	SetItems(Items, GameContext);
	if (Item->GetItemState(GameContext) != EInventoryItemState::ItemState_Custom)
	{
		// Automatically change item state if the designer is not handling it himself.
		Item->SetItemState(EInventoryItemState::ItemState_Used, GameContext);
	}
	if (!bIsUpdating)
	{
		InventoryChanged.Broadcast(TArray<UInventoryItem*> {Item });
	}
	else
	{
		ModifiedItems.Add(Item);
	}
	Item->OnRemovedFromInventory(this, GameContext);
	// While it might be better for the event to be raised by OnRemovedFromInventory, that could be easily forgotten by designers overriding that. And we don't want that.
	Item->RemovedFromInventory.Broadcast(Item);
	return true;
}

void UInventory::BeginUpdate()
{
	bIsUpdating = true;
	ModifiedItems.Empty();
}

void UInventory::EndUpdate()
{
	if (bIsUpdating)
	{
		InventoryChanged.Broadcast(ModifiedItems);
		ModifiedItems.Empty();
	}
	else
	{
		check (false && "This method should only be called between begin update and end update calls.")
	}
	bIsUpdating = false;
}

TArray<UInventoryItem*> UInventory::GetItems(UAdventurePluginGameContext* GameContext)
{
	TArray<UInventoryItem*> InventoryItems = TArray<UInventoryItem*>();
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("Inventory:GetItems")))
	{
		return InventoryItems;
	}

	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;
	for (TSubclassOf<UInventoryItem>& ItemClass : SaveGame->StorageInventory)
	{
		InventoryItems.Add(GameContext->ItemManager->GetItem(ItemClass));
	}
	return InventoryItems;
}

void UInventory::SetItems(const TArray<UInventoryItem*>& NewItems, UAdventurePluginGameContext* GameContext)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("Inventory:SetItems")))
	{
		return;
	}

	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;
	SaveGame->StorageInventory.Empty();
	for (const UInventoryItem* Item : NewItems)
	{
		SaveGame->StorageInventory.Add(Item->GetClass());
	}
}