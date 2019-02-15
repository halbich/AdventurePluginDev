#include "SimpleCombinationWithSingleItem.h"
#include "AdventurePluginGameContext.h"
#include "AdventurePluginRuntime.h"
#include "InventoryController.h"
#include "ItemManager.h"
#include "Inventory.h"

void USimpleCombinationWithSingleItem::Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("SimpleCombinationWithSingleItem:Execute")))
	{
		return;
	}
	UInventoryItem* ResultItem = GameContext->ItemManager->GetItem(ResultItemClass);
	if (!IsValid(ResultItem))
	{
		LOG_Warning(NSLOCTEXT("AP", "SimpleCombinationWithSingleItem_ExecuteResultNull", "SimpleCombinationWithSingleItem:CanCombineWith::The result item is null or invalid."));
		return;
	}
	UInventoryItem* SourceItem = Cast<UInventoryItem>(CombinationSource);
	UInventoryItem* TargetItem = Cast<UInventoryItem>(CombinationTarget);
	GameContext->InventoryController->GetInventory()->BeginUpdate();
	if (IsValid(SourceItem))
	{
		GameContext->InventoryController->GetInventory()->RemoveItem(SourceItem, GameContext);
	}
	if (IsValid(TargetItem))
	{
		GameContext->InventoryController->GetInventory()->RemoveItem(TargetItem, GameContext);
	}
	GameContext->InventoryController->GetInventory()->AddItem(ResultItem, GameContext);
	GameContext->InventoryController->GetInventory()->EndUpdate();
}

bool USimpleCombinationWithSingleItem::CanCombineWith_Implementation(UObject* CombinationSource, UObject* CombinationTarget)
{
	if (!IsValid(CombinationTarget))
	{
		LOG_Warning(NSLOCTEXT("AP", "SimpleCombinationWithSingleItem_CanCombineWithNullItem", "SimpleCombinationWithSingleItem:CanCombineWith::The other item is null or invalid."));
		return false;
	}
	return CombinationTarget->GetClass()->IsChildOf(TargetClass);
}