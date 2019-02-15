#include "InventoryItem.h"
#include "AdventurePluginSaveGame.h"
#include "Inventory.h"
#include "AdventurePluginGameContext.h"
#include "ItemManager.h"
#include "AdventurePluginBlueprintLibrary.h"

void UInventoryItem::Examine_Implementation(UAdventurePluginGameContext* GameContext)
{
	UAdventurePluginBlueprintLibrary::ShowDialogFromEntryPoint(GameContext, ExamineDialog);
}

void UInventoryItem::Use_Implementation(UAdventurePluginGameContext* GameContext)
{

}

bool UInventoryItem::WasPickedUp_Implementation(UAdventurePluginGameContext* GameContext)
{
	EInventoryItemState ItemState = GetItemState(GameContext);
	return ItemState != EInventoryItemState::ItemState_NotSpawned && ItemState != EInventoryItemState::ItemState_Spawned && ItemState != EInventoryItemState::ItemState_Invalid;
}

EInventoryItemState UInventoryItem::GetItemState(UAdventurePluginGameContext* GameContext)
{
	if (!IsValid(GameContext) || !IsValid(GameContext->SaveGame))
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextInvalid", "InventoryItem::GetItemState::gameContext is invalid"));
		return EInventoryItemState::ItemState_Invalid;
	}

	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;

	return SaveGame->GetItemStateOrDefault(GetClass(), EInventoryItemState::ItemState_Invalid);
}

void UInventoryItem::SetItemState(EInventoryItemState NewValue, UAdventurePluginGameContext* GameContext)
{
	if (!IsValid(GameContext) || !IsValid(GameContext->SaveGame))
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextInvalid", "InventoryItem::GetItemState::gameContext is invalid"));
		return;
	}

	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;
	SaveGame->SetItemState(GetClass(), NewValue);
}
void UInventoryItem::OnAddedToInventory_Implementation(UInventory* Inventory, UAdventurePluginGameContext* GameContext)
{
}
void UInventoryItem::OnRemovedFromInventory_Implementation(UInventory* Inventory, UAdventurePluginGameContext* GameContext)
{
}

bool UInventoryItem::IsExaminable_Implementation(UAdventurePluginGameContext* GameContext)
{
	return bDefaultIsExaminable;
}

bool UInventoryItem::IsPickable_Implementation(UAdventurePluginGameContext* GameContext)
{
	if (!IsValid(GameContext) || !IsValid(GameContext->InventoryController))
	{
		// TODO: Log error.
		return false;
	}
	return bDefaultIsPickable && !GameContext->InventoryController->GetInventory()->HasItem(this, GameContext);
}
bool UInventoryItem::IsUsable_Implementation(UAdventurePluginGameContext* GameContext)
{
	return bDefaultIsUsable;
}