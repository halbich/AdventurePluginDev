// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginBlueprintLibrary.h"
#include "ItemManager.h"
#include "AdventurePluginGameContext.h"

#pragma optimize("", off)
UFUNCTION(BlueprintCallable, Category = "AdventurePluginBPLibrary")
void UAdventurePluginBlueprintLibrary::ShowDialogFromEntryPoint(UAdventurePluginGameContext* gameContext, UDialogGraph* graph, UDialogGraphNode* startNode) {
	if (!gameContext || !gameContext->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "Show dialog::gameContext is NULL"));
		return;
	}

	if (!graph || !graph->IsValidLowLevel())
	{
		LOG_Warning(NSLOCTEXT("AP", "DialogGraphNull", "Show dialog::graph is NULL"));
		return;
	}

	auto dc = gameContext->DialogueController;
	if (!dc || !dc->IsValidLowLevel())
	{
		LOG_Warning(NSLOCTEXT("AP", "DialogControllerNull", "Show dialog::gameContext->DialogueController is NULL"));
		return;
	}
	if (startNode == nullptr) {
		startNode = graph->MainEntryPoint;
	}
	dc->ShowDialog(gameContext, graph, startNode);
}
void UAdventurePluginBlueprintLibrary::ShowDialog(UAdventurePluginGameContext* gameContext, UDialogGraph* graph)
{
	ShowDialogFromEntryPoint(gameContext, graph, nullptr);
}

void UAdventurePluginBlueprintLibrary::ShowInventory(UAdventurePluginGameContext* gameContext, bool bShow)
{
	if (!gameContext || !gameContext->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "ShowInventory dialog::gameContext is NULL"));
		return;
	}

	auto ic = gameContext->InventoryController;
	if (!ic || !ic->IsValidLowLevel())
	{
		LOG_Warning(NSLOCTEXT("AP", "InventoryControllerNull", "ShowInventory::gameContext->InventoryController is NULL"));
		return;
	}

	if (bShow)
		ic->ShowInventory(gameContext);
	else
		ic->HideInventory();
}


UInventoryItem* UAdventurePluginBlueprintLibrary::GetItem(UAdventurePluginGameContext* gameContext, TSubclassOf<UInventoryItem> Item)
{
	if (!gameContext || !gameContext->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "GetItem::gameContext is NULL"));
		return nullptr;
	}
	auto* itemManager = gameContext->ItemManager;
	if (!itemManager || !itemManager->IsValidLowLevel())
	{
		LOG_Warning(NSLOCTEXT("AP", "ItemManagerNull", "GetItem::gameContext->ItemManager is NULL"));
		return nullptr;
	}
	return itemManager->GetItem(Item);
}

#pragma optimize("", on)