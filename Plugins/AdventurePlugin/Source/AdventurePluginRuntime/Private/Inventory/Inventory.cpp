#include "Inventory/Inventory.h"
#include "SaveGame/AdventurePluginSaveGame.h"
#include "Common/AdventurePluginGameContext.h"
#include "Combinations/CombinableObjectManager.h"

bool UInventory::HasItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	return GetItems(GameContext, WorldObjectContext).Contains(Item);
}

bool UInventory::AddItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	// Add an item, change item state and raise all events as necessary.
	TArray<UInventoryItem*> Items = GetItems(GameContext, WorldObjectContext);
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

bool UInventory::RemoveItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	// Remove item, change item state and raise all events as necessary.
	TArray<UInventoryItem*> Items = GetItems(GameContext, WorldObjectContext);
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

TArray<UInventoryItem*> UInventory::GetItems(UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	TArray<UInventoryItem*> InventoryItems = TArray<UInventoryItem*>();
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("Inventory:GetItems")))
	{
		return InventoryItems;
	}

	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;
	for (TSubclassOf<UInventoryItem>& ItemClass : SaveGame->StorageInventory)
	{
		;
		InventoryItems.Add(Cast<UInventoryItem>(GameContext->CombinableObjectManager->GetCombinableObjectInstance(ItemClass, WorldObjectContext)));
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