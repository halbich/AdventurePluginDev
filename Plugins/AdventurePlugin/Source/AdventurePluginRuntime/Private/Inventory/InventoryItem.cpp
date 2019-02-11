#include "InventoryItem.h"
#include "AdventurePluginBlueprintLibrary.h"

void UInventoryItem::Examine_Implementation(UAdventurePluginGameContext* GameContext)
{
	UAdventurePluginBlueprintLibrary::ShowDialogFromEntryPoint(GameContext, ExamineDialog);
}

void UInventoryItem::Use_Implementation(UAdventurePluginGameContext* GameContext)
{

}

bool UInventoryItem::WasPickedUp_Implementation()
{
	return ItemState != EInventoryItemState::ItemState_NotSpawned && ItemState != EInventoryItemState::ItemState_Spawned;
}