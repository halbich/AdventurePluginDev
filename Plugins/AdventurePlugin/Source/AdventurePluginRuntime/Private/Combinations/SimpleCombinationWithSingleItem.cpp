#include "Combinations/SimpleCombinationWithSingleItem.h"
#include "Common/AdventurePluginGameContext.h"
#include "AdventurePluginRuntime.h"
#include "Inventory/Controller/InventoryController.h"
#include "Inventory/ItemManager.h"
#include "Inventory/Inventory.h"

void USimpleCombinationWithSingleItem::Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("SimpleCombinationWithSingleItem:Execute")))
	{
		return;
	}
	UInventoryItem* ResultItem = GameContext->ItemManager->GetItem(ResultItemClass, this);
	if (!IsValid(ResultItem))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "SimpleCombinationWithSingleItem_ExecuteResultNull", "SimpleCombinationWithSingleItem:Execute::The result item is null or invalid."));
		return;
	}
	UInventoryItem* SourceItem = Cast<UInventoryItem>(CombinationSource);
	UInventoryItem* TargetItem = Cast<UInventoryItem>(CombinationTarget);
	GameContext->InventoryController->GetInventory()->BeginUpdate();
	if (IsValid(SourceItem))
	{
		GameContext->InventoryController->GetInventory()->RemoveItem(SourceItem, GameContext, this);
	}
	if (IsValid(TargetItem))
	{
		GameContext->InventoryController->GetInventory()->RemoveItem(TargetItem, GameContext, this);
	}
	GameContext->InventoryController->GetInventory()->AddItem(ResultItem, GameContext, this);
	GameContext->InventoryController->GetInventory()->EndUpdate();
}