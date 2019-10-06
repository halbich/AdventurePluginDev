#include "Inventory/InventoryItem.h"
#include "SaveGame/AdventurePluginSaveGame.h"
#include "Inventory/Inventory.h"
#include "Common/AdventurePluginGameContext.h"
#include "BlueprintLibrary/AdventurePluginBlueprintLibrary.h"

bool UInventoryItem::WasPickedUp_Implementation(UAdventurePluginGameContext* GameContextOverride)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
	EInventoryItemState ItemState = GetItemState(GameContext);
	return ItemState != EInventoryItemState::ItemState_NotSpawned && ItemState != EInventoryItemState::ItemState_Spawned && ItemState != EInventoryItemState::ItemState_Invalid;
}

EInventoryItemState UInventoryItem::GetItemState(UAdventurePluginGameContext* GameContextOverride)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("InventoryItem:GetItemState")))
	{
		return EInventoryItemState::ItemState_Invalid;
	}

	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;

	return SaveGame->GetItemStateOrDefault(GetClass(), DefaultItemState);
}

void UInventoryItem::SetItemState(EInventoryItemState NewValue, UAdventurePluginGameContext* GameContextOverride)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("InventoryItem:SetItemState")))
	{
		return;
	}
	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;
	SaveGame->SetItemState(GetClass(), NewValue);
	ItemStateChanged.Broadcast(this);
}

void UInventoryItem::OnAddedToInventory_Implementation(UInventory* Inventory, UAdventurePluginGameContext* GameContextOverride)
{
}

void UInventoryItem::OnRemovedFromInventory_Implementation(UInventory* Inventory, UAdventurePluginGameContext* GameContextOverride)
{
}

bool UInventoryItem::IsPickable_Implementation(UAdventurePluginGameContext* GameContextOverride)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("InventoryItem:IsPickable")))
	{
		return false;
	}
	return bDefaultIsPickable && !GameContext->InventoryController->GetInventory()->HasItem(this, GameContext, this);
}