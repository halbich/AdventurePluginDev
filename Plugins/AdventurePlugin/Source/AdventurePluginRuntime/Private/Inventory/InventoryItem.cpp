#include "InventoryItem.h"
#include "AdventurePluginBlueprintLibrary.h"

void UInventoryItem::Examine_Implementation(UAdventurePluginGameContext* Context)
{
	UAdventurePluginBlueprintLibrary::ShowDialogFromEntryPoint(Context, ExamineDialog);
}

void UInventoryItem::Use_Implementation(UAdventurePluginGameContext* Context)
{

}

bool UInventoryItem::WasPickedUp_Implementation()
{
	return ItemState != EInventoryItemState::ItemState_NotSpawned && ItemState != EInventoryItemState::ItemState_Spawned;
}