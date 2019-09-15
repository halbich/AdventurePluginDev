#pragma once

#include "CoreMinimal.h"
#include "AdventurePluginRuntime.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Common/AdventurePluginGameContext.h"
#include "Dialog/Controller/DialogController.h"
#include "Quest/Graph/QuestGraph.h"
#include "Dialog/Graph/DialogGraph.h"
#include "Dialog/Graph/DialogGraphNode.h"
#include "Dialog/Structs/DialogGraphEntryPoint.h"
#include "Inventory/Controller/InventoryController.h"
#include "AdventurePluginRuntime.h"
#include "AdventureCharacter.h"
#include "Inventory/InventoryItem.h"
#include "Inventory/Inventory.h"
#include "AdventurePluginBlueprintLibrary.generated.h"

/**
* Blueprint library for all global Adventure Plugin methods that do not belong to any other category.
*/
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Starts a dialog from an entry point.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param EntryPoint Specifies the place from which the dialog should begin, both the dialog graph and the entry point.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Dialog", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static void ShowDialogFromEntryPoint(UAdventurePluginGameContext* GameContextOverride, FDialogGraphEntryPoint EntryPoint, UObject* WorldObjectContext);

	/**
	* Starts the specified dialog from the main entry point.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param DialogGraph Specifies the graph containing the dialog that should be displayed.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Dialog", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static void ShowDialog(UAdventurePluginGameContext* GameContextOverride, UDialogGraph* DialogGraph, UObject* WorldObjectContext);

	/**
	* Retrieves the inventory.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Inventory", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static UInventory* GetInventory(UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext);

	/**
	* Hides the inventory.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Inventory", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static void HideInventory(UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext);

	/**
	* Shows or hides the inventory.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param bVisible If true, the method should show the inventory. If false, the method should hide the inventory.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Inventory", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static void SetInventoryVisibility(UAdventurePluginGameContext* GameContextOverride, bool bVisible, UObject* WorldObjectContext);

	/**
	* Shows the inventory.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Inventory", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static void ShowInventory(UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext);

	/**
	* Adds an item to the player's inventory
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param Item The item to add to the inventory.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Inventory", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static void AddItemToInventory(UAdventurePluginGameContext* GameContextOverride, UInventoryItem* Item, UObject* WorldObjectContext);

	/**
	* Remoes an item from the player's inventory
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param Item The item to remove from the inventory.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Inventory", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static void RemoveItemFromInventory(UAdventurePluginGameContext* GameContextOverride, UInventoryItem* Item, UObject* WorldObjectContext);

	/**
	* Checks if the player has the specified item in inventory.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param Item The item whose existence is in question.
	* @return True if the specified item is in inventory, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Inventory", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static bool HasItemInInventory(UAdventurePluginGameContext* GameContextOverride, UInventoryItem* Item, UObject* WorldObjectContext);

	/**
	* Retrieves the only instance of the requested item class. Necessary to access any functionality provided by the Item class. Always use this method, never instantiate UInventoryItem directly.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param Item The class whose instance is requested.
	* @return The only instance of this item.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Inventory", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static UInventoryItem* GetItem(UAdventurePluginGameContext* GameContextOverride, TSubclassOf<UInventoryItem> Item, UObject* WorldObjectContext);

	/**
	* Retrieves the only instance of the requested character class. Neccessary to access any functionality provided by the Character class. Always use this method, never instantiate UAdventureCharacter directly.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param Character The class whose instance is requested.
	* @return The only instance of this character.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Character", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static UAdventureCharacter* GetAdventureCharacter(UAdventurePluginGameContext* GameContextOverride, TSubclassOf<UAdventureCharacter> Character, UObject* WorldObjectContext);

private:
};
