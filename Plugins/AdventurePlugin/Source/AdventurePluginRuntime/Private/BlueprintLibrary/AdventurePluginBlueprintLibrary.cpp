// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginBlueprintLibrary.h"
#include "ItemManager.h"
#include "AdventureCharacterManager.h"
#include "AdventurePluginGameContext.h"
#include "AdventurePluginGameInstance.h"

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

void UAdventurePluginBlueprintLibrary::ShowInventory(UAdventurePluginGameContext* GameContext)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("ShowInventory")))
	{
		return;
	}
	UInventoryController* InventoryController = GameContext->InventoryController;
	InventoryController->ShowInventory(GameContext);
}

void UAdventurePluginBlueprintLibrary::HideInventory(UAdventurePluginGameContext* GameContext)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("HideInventory")))
	{
		return;
	}
	UInventoryController* InventoryController = GameContext->InventoryController;
	InventoryController->HideInventory();
}

void UAdventurePluginBlueprintLibrary::SetInventoryVisibility(UAdventurePluginGameContext* GameContext, bool bVisible)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("ShowInventory")))
	{
		return;
	}

	UInventoryController* InventoryController = GameContext->InventoryController;

	if (bVisible)
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
	if (!IsValid(GameInstance))
	{
		LOG_Error(NSLOCTEXT("AP", "GetCurrentGameContext_GameInstanceNotValid", "GetCurrentGameContext provided by Adventure Plugin can only be used if the game instance inherits from UAdventurePluginGameInstance"));
		return nullptr;
	}
	if (!UAdventurePluginGameContext::IsGameContextValid(GameInstance->CurrentGameContext, TEXT("GetCurrentGameContext")))
	{
		return nullptr;
	}
	return GameInstance->CurrentGameContext;
}
