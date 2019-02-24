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
		LOG_Error(NSLOCTEXT("AdventurePlugin", "AdventurePluginBlueprintLibrary_ShowDialog_DialogGraphNull", "Show dialog::graph is NULL"));
		return;
	}

	UDialogController* DialogController = GameContext->DialogController;
	UDialogGraphNode** StartNode = DialogGraph->IdToNodeMap.Find(EntryPoint.EntryPointName);
	if (StartNode == nullptr)
	{
		// The name was not found in the on the graph. Use the main entry point.
		StartNode = &DialogGraph->MainEntryPoint;
		// This could be on purpose if the name was not specified or was explicitly main entry point. Otherwise we have an invalid entry point name and we should show a warning.
		if (EntryPoint.EntryPointName != UDialogGraph::MainEntryName && !EntryPoint.EntryPointName.IsNone())
		{
			LOG_Warning(NSLOCTEXT("AdventurePlugin", "AdventurePluginBlueprintLibrary_ShowDialog_InvalidEntryPoint", "ShowDialog:Entry point name is invalid"));
		}
	}
	if (StartNode == nullptr || !IsValid(*StartNode)) 
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "AdventurePluginBlueprintLibrary_ShowDialog_NoMainEntryPoint", "ShowDialog:Main entry point should be used, but was not found."));
		return;
	}

	DialogController->ShowDialog(GameContext, DialogGraph, *StartNode);
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
	GameContext->InventoryController->ShowInventory(GameContext);
}

void UAdventurePluginBlueprintLibrary::HideInventory(UAdventurePluginGameContext* GameContext)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("HideInventory")))
	{
		return;
	}
	GameContext->InventoryController->HideInventory(GameContext);
}

void UAdventurePluginBlueprintLibrary::SetInventoryVisibility(UAdventurePluginGameContext* GameContext, bool bVisible)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("ShowInventory")))
	{
		return;
	}

	if (bVisible)
	{
		GameContext->InventoryController->ShowInventory(GameContext);
	}
	else
	{
		GameContext->InventoryController->HideInventory(GameContext);
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
		LOG_Error(NSLOCTEXT("AdventurePlugin", "AdventurePluginBlueprintLibrary_GetCurrentGameContext_GameInstanceNotValid", "GetCurrentGameContext provided by Adventure Plugin can only be used if the game instance inherits from UAdventurePluginGameInstance"));
		return nullptr;
	}
	if (!UAdventurePluginGameContext::IsGameContextValid(GameInstance->CurrentGameContext, TEXT("GetCurrentGameContext")))
	{
		return nullptr;
	}
	return GameInstance->CurrentGameContext;
}
