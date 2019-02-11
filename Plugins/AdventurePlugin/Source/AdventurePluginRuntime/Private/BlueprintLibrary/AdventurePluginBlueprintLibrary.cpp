// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginBlueprintLibrary.h"
#include "ItemManager.h"
#include "AdventureCharacterManager.h"
#include "AdventurePluginGameContext.h"

#pragma optimize("", off)

void UAdventurePluginBlueprintLibrary::ShowDialogFromEntryPoint(UAdventurePluginGameContext* GameContext, FDialogGraphEntryPoint EntryPoint)
{
	if (!GameContext || !GameContext->IsValidLowLevel())
	{
		// TODO: Error.
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "Show dialog::gameContext is NULL"));
		return;
	}

	UDialogGraph* DialogGraph = EntryPoint.Dialog;
	if (!DialogGraph || !DialogGraph->IsValidLowLevel())
	{
		// TODO: Error.
		LOG_Warning(NSLOCTEXT("AP", "DialogGraphNull", "Show dialog::graph is NULL"));
		return;
	}

	UDialogController* DialogController = GameContext->DialogController;
	if (!DialogController || !DialogController->IsValidLowLevel())
	{
		// TODO: Error.
		LOG_Warning(NSLOCTEXT("AP", "DialogControllerNull", "Show dialog::gameContext->DialogController is NULL"));
		return;
	}

	UDialogGraphNode* StartNode;
	if (EntryPoint.EntryPointName == UDialogGraph::MainEntryName)
	{
		StartNode = DialogGraph->MainEntryPoint;
	}
	else
	{
		StartNode = *DialogGraph->IdToNodeMap.Find(EntryPoint.EntryPointName);
	}
	if (StartNode == nullptr) StartNode = DialogGraph->MainEntryPoint;

	DialogController->ShowDialog(GameContext, DialogGraph, StartNode);
}

void UAdventurePluginBlueprintLibrary::ShowDialog(UAdventurePluginGameContext* GameContext, UDialogGraph* DialogGraph)
{
	FDialogGraphEntryPoint EntryPoint;
	EntryPoint.Dialog = DialogGraph;
	EntryPoint.EntryPointName = UDialogGraph::MainEntryName;

	ShowDialogFromEntryPoint(GameContext, EntryPoint);
}

void UAdventurePluginBlueprintLibrary::ShowInventory(UAdventurePluginGameContext* GameContext, bool bShow)
{
	if (!GameContext || !GameContext->IsValidLowLevel())
	{
		// TODO: Error.
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "ShowInventory dialog::gameContext is NULL"));
		return;
	}

	UInventoryController* InventoryController = GameContext->InventoryController;
	if (!InventoryController || !InventoryController->IsValidLowLevel())
	{
		// TODO: Error.
		LOG_Warning(NSLOCTEXT("AP", "InventoryControllerNull", "ShowInventory::gameContext->InventoryController is NULL"));
		return;
	}

	if (bShow)
	{
		InventoryController->ShowInventory(GameContext);
	}
	else
	{
		InventoryController->HideInventory();
	}
}


UInventoryItem* UAdventurePluginBlueprintLibrary::GetItem(UAdventurePluginGameContext* GameContext, TSubclassOf<UInventoryItem> Item)
{
	if (!GameContext || !GameContext->IsValidLowLevel())
	{
		// TODO: Error.
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "GetItem::gameContext is NULL"));
		return nullptr;
	}
	UItemManager* ItemManager = GameContext->ItemManager;
	if (!ItemManager || !ItemManager->IsValidLowLevel())
	{
		// TODO: Error.
		LOG_Warning(NSLOCTEXT("AP", "ItemManagerNull", "GetItem::gameContext->ItemManager is NULL"));
		return nullptr;
	}
	return ItemManager->GetItem(Item);
}

UAdventureCharacter* UAdventurePluginBlueprintLibrary::GetAdventureCharacter(UAdventurePluginGameContext* GameContext, TSubclassOf<UAdventureCharacter> Character)
{
	if (!GameContext || !GameContext->IsValidLowLevel())
	{
		// TODO: Error.
		LOG_Error(NSLOCTEXT("AP", "GetAdventureCharacterGameContextNull", "GetAdventureCharacter::gameContext is NULL"));
		return nullptr;
	}
	UAdventureCharacterManager* CharacterManager = GameContext->AdventureCharacterManager;
	if (!CharacterManager || !CharacterManager->IsValidLowLevel())
	{
		// TODO: Error.
		LOG_Warning(NSLOCTEXT("AP", "AdventureCharacterManagerNull", "GetAdventureCharacter::gameContext->AdventureCharacterManager is NULL"));
		return nullptr;
	}
	return CharacterManager->GetCharacter(Character);
}

bool UAdventurePluginBlueprintLibrary::BindQuestEvent(UAdventurePluginGameContext* GameContext, UQuestGraph* QuestGraph, FName EventName, FQuestEvent QuestEvent)
{
	if (!GameContext || !GameContext->IsValidLowLevel())
	{
		// TODO: Error.
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "GetItem::gameContext is NULL"));
		return false;
	}	

	if (!QuestGraph || !QuestGraph->IsValidLowLevel())
	{
		// TODO: Error.
		LOG_Warning(NSLOCTEXT("AP", "QuestGraphNull", "Bind event::graph is NULL"));
		return false;
	}

	TMap<FName, FQuestEvent>& QuestEventsMap = QuestGraph->QuestEvents;
	if (!QuestEventsMap.Contains(EventName))
	{
		// TODO: Error.
		LOG_Warning(NSLOCTEXT("AP", "EventNameUndefined", "Bind event::event name is not defined in quest"));
		return false;
	}

	QuestEventsMap.Add(EventName, QuestEvent);
	return true;
}

#pragma optimize("", on)