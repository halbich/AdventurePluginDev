#include "CombineIntoOneItemCombinationAction.h"
#include "Common/AdventurePluginGameContext.h"
#include "Combinations/CombinableObjectManager.h"
#include "BlueprintLibrary/AdventurePluginBlueprintLibrary.h"

void UCombineIntoOneItemCombinationAction::Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("SimpleCombinationWithSingleItem:Execute")))
	{
		return;
	}
	UInventoryItem* ResultItem = Cast<UInventoryItem>(GameContext->CombinableObjectManager->GetCombinableObjectInstance(ResultItemClass, this));
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