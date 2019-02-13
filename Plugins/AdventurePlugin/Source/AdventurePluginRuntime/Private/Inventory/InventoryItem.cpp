#include "InventoryItem.h"
#include "AdventurePluginSaveGame.h"
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
	if (!GameContext || !GameContext->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "InventoryItem::GetItemState::gameContext is NULL"));
		return EInventoryItemState::ItemState_Invalid;
	}

	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;
	if (!SaveGame || !SaveGame->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextSaveGameNull", "InventoryItem::GetItemState::gameContext::SaveGame is NULL"));
		return EInventoryItemState::ItemState_Invalid;
	}

	return SaveGame->GetItemStateOrDefault(GetClass(), EInventoryItemState::ItemState_Invalid);
}

void UInventoryItem::SetItemState(EInventoryItemState NewValue, UAdventurePluginGameContext* GameContext)
{
	if (!GameContext || !GameContext->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "InventoryItem::SetItemState::gameContext is NULL"));
		return;
	}

	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;
	if (!SaveGame || !SaveGame->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextSaveGameNull", "InventoryItem::SetItemState::gameContext::SaveGame is NULL"));
		return;
	}
	SaveGame->SetItemState(GetClass(), NewValue);
}