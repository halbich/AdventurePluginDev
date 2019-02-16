// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginBlueprintLibrary.h"
#include "ItemManager.h"
#include "AdventureCharacterManager.h"
#include "AdventurePluginGameContext.h"
#include "AdventurePluginGameInstance.h"

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

UAdventurePluginGameContext* UAdventurePluginBlueprintLibrary::GetCurrentGameContext(UObject* WorldObjectContext)
{
	UAdventurePluginGameInstance* GameInstance = Cast<UAdventurePluginGameInstance>(UGameplayStatics::GetGameInstance(WorldObjectContext));
	return GameInstance->CurrentGameContext;
}

#pragma optimize("", on)