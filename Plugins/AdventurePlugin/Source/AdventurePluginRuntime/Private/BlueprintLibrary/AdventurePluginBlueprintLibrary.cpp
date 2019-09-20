#include "BlueprintLibrary/AdventurePluginBlueprintLibrary.h"
#include "Inventory/ItemManager.h"
#include "Inventory/Inventory.h"
#include "AdventureCharacterManager.h"
#include "Common/AdventurePluginGameContext.h"
#include "Common/AdventurePluginGameInstance.h"

void UAdventurePluginBlueprintLibrary::ShowDialogFromEntryPoint(UAdventurePluginGameContext* GameContextOverride, FDialogGraphEntryPoint EntryPoint, UObject* WorldObjectContext)
{
	auto GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
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

	DialogController->ShowDialog(GameContext, DialogGraph, *StartNode, WorldObjectContext);
}

void UAdventurePluginBlueprintLibrary::ShowDialog(UAdventurePluginGameContext* GameContextOverride, UDialogGraph* DialogGraph, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	FDialogGraphEntryPoint EntryPoint;
	EntryPoint.Dialog = DialogGraph;
	EntryPoint.EntryPointName = UDialogGraph::MainEntryName;

	ShowDialogFromEntryPoint(GameContext, EntryPoint, WorldObjectContext);
}

void UAdventurePluginBlueprintLibrary::ShowInventory(UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("ShowInventory")))
	{
		return;
	}
	GameContext->InventoryController->ShowInventory(GameContext);
}
UInventory* UAdventurePluginBlueprintLibrary::GetInventory(UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("GetInventory")))
	{
		return nullptr;
	}
	return GameContext->InventoryController->GetInventory();
}

void UAdventurePluginBlueprintLibrary::HideInventory(UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("HideInventory")))
	{
		return;
	}
	GameContext->InventoryController->HideInventory(GameContext);
}

void UAdventurePluginBlueprintLibrary::SetInventoryVisibility(UAdventurePluginGameContext* GameContextOverride, bool bVisible, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
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
void UAdventurePluginBlueprintLibrary::AddItemToInventory(UAdventurePluginGameContext* GameContextOverride, UInventoryItem* Item, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("AddItemToInventory")))
	{
		return;
	}
	if (!IsValid(Item))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "AdventurePluginBlueprintLibrary_AddItemToInventory_ItemNotValid", "AddItemToInventory: Invalid item passed as an argument."));
		return;
	}
	UInventory* Inventory = GameContext->InventoryController->GetInventory();
	if (!IsValid(Inventory))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "AdventurePluginBlueprintLibrary_AddItemToInventory_InventoryNotValid", "AddItemToInventory: The inventory on on the inventory controller is not valid."));
		return;
	}
	Inventory->AddItem(Item, GameContext, WorldObjectContext);
}
void UAdventurePluginBlueprintLibrary::RemoveItemFromInventory(UAdventurePluginGameContext* GameContextOverride, UInventoryItem* Item, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("RemoveItemFromInventory")))
	{
		return;
	}
	if (!IsValid(Item))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "AdventurePluginBlueprintLibrary_RemoveItemFromInventory_ItemNotValid", "RemoveItemFromInventory: Invalid item passed as an argument."));
		return;
	}
	UInventory* Inventory = GameContext->InventoryController->GetInventory();
	if (!IsValid(Inventory))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "AdventurePluginBlueprintLibrary_RemoveItemFromInventory_InventoryNotValid", "RemoveItemFromInventory: The inventory on on the inventory controller is not valid."));
		return;
	}
	Inventory->RemoveItem(Item, GameContext, WorldObjectContext);
}
bool UAdventurePluginBlueprintLibrary::HasItemInInventory(UAdventurePluginGameContext* GameContextOverride, UInventoryItem* Item, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("HasItemInInventory")))
	{
		return false;
	}
	if (!IsValid(Item))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "AdventurePluginBlueprintLibrary_HasItemInInventory_ItemNotValid", "HasItemInInventory: Invalid item passed as an argument."));
		return false;
	}
	UInventory* Inventory = GameContext->InventoryController->GetInventory();
	if (!IsValid(Inventory))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "AdventurePluginBlueprintLibrary_HasItemInInventory_InventoryNotValid", "HasItemInInventory: The inventory on on the inventory controller is not valid."));
		return false;
	}
	return Inventory->HasItem(Item, GameContext, WorldObjectContext);
}

UInventoryItem* UAdventurePluginBlueprintLibrary::GetItem(UAdventurePluginGameContext* GameContextOverride, TSubclassOf<UInventoryItem> Item, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("GetItem")))
	{
		return nullptr;
	}
	UItemManager* ItemManager = GameContext->ItemManager;
	return ItemManager->GetItem(Item, WorldObjectContext);
}

UAdventureCharacter* UAdventurePluginBlueprintLibrary::GetAdventureCharacter(UAdventurePluginGameContext* GameContextOverride, TSubclassOf<UAdventureCharacter> Character, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("GetAdventureCharacter")))
	{
		return nullptr;
	}
	UAdventureCharacterManager* CharacterManager = GameContext->AdventureCharacterManager;
	return CharacterManager->GetCharacter(Character, WorldObjectContext);
}