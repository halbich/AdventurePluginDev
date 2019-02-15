// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginBlueprintLibrary.h"
#include "ItemManager.h"
#include "AdventureCharacterManager.h"
#include "AdventurePluginGameContext.h"

#pragma optimize("", off)

void UAdventurePluginBlueprintLibrary::ShowDialogFromEntryPoint(UAdventurePluginGameContext* GameContext, FDialogGraphEntryPoint EntryPoint)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("ShowDialogFromEntryPoint")))
	{
		return;
	}

	UDialogGraph* DialogGraph = EntryPoint.Dialog;
	if (!IsValid(DialogGraph))
	{
		LOG_Warning(NSLOCTEXT("AP", "DialogGraphNull", "Show dialog::graph is NULL"));
		return;
	}

	UDialogController* DialogController = GameContext->DialogController;

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
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("ShowInventory")))
	{
		return;
	}

	UInventoryController* InventoryController = GameContext->InventoryController;

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
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("GetItem")))
	{
		return nullptr;
	}
	UItemManager* ItemManager = GameContext->ItemManager;
	return ItemManager->GetItem(Item);
}

UAdventureCharacter* UAdventurePluginBlueprintLibrary::GetAdventureCharacter(UAdventurePluginGameContext* GameContext, TSubclassOf<UAdventureCharacter> Character)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("GetAdventureCharacter")))
	{
		return nullptr;
	}
	UAdventureCharacterManager* CharacterManager = GameContext->AdventureCharacterManager;
	return CharacterManager->GetCharacter(Character);
}

bool UAdventurePluginBlueprintLibrary::BindQuestEvent(UAdventurePluginGameContext* GameContext, UQuestGraph* QuestGraph, FName EventName, FQuestEvent QuestEvent)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("BindQuestEvent")))
	{
		return false;
	}	

	if (!IsValid(QuestGraph))
	{
		LOG_Warning(NSLOCTEXT("AP", "QuestGraphInvalid", "Bind event::graph is invalid"));
		return false;
	}

	TMap<FName, FQuestEvent>& QuestEventsMap = QuestGraph->QuestEvents;
	if (!QuestEventsMap.Contains(EventName))
	{
		LOG_Warning(NSLOCTEXT("AP", "EventNameUndefined", "Bind event::event name is not defined in quest"));
		return false;
	}

	QuestEventsMap.Add(EventName, QuestEvent);
	return true;
}

#pragma optimize("", on)