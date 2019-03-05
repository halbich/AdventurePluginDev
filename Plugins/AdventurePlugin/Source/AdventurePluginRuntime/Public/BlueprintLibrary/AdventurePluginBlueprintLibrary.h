#pragma once

#include "AdventurePluginRuntime.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogController.h"
#include "Quest/Graph/QuestGraph.h"
#include "Dialog/Graph/DialogGraph.h"
#include "Dialog/Graph/DialogGraphNode.h"
#include "Dialog/Structs/DialogGraphEntryPoint.h"
#include "InventoryController.h"
#include "AdventurePluginRuntime.h"
#include "AdventureCharacter.h"
#include "InventoryItem.h"
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
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Dialog")
	static void ShowDialogFromEntryPoint(UAdventurePluginGameContext* GameContext, FDialogGraphEntryPoint EntryPoint);

	/**
	* Starts the specified dialog from the main entry point.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param DialogGraph Specifies the graph containing the dialog that should be displayed.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Dialog")
	static void ShowDialog(UAdventurePluginGameContext* GameContext, UDialogGraph* DialogGraph);

	/**
	* Hides the inventory.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Inventory")
	static void HideInventory(UAdventurePluginGameContext* GameContext);

	/**
	* Shows or hides the inventory.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param bVisible If true, the method should show the inventory. If false, the method should hide the inventory.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Inventory")
	static void SetInventoryVisibility(UAdventurePluginGameContext* GameContext, bool bVisible);

	/**
	* Shows the inventory.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Inventory")
	static void ShowInventory(UAdventurePluginGameContext* GameContext);

	/**
	* Adds an item to the player's inventory
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param Item The item to add to the inventory.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Inventory")
	static void AddItemToInventory(UAdventurePluginGameContext* GameContext, UInventoryItem* Item);

	/**
	* Remoes an item from the player's inventory
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param Item The item to remove from the inventory.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Inventory")
	static void RemoveItemFromInventory(UAdventurePluginGameContext* GameContext, UInventoryItem* Item);

	/**
	* Checks if the player has the specified item in inventory.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param Item The item whose existence is in question.
	* @return True if the specified item is in inventory, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Inventory")
	static bool HasItemInInventory(UAdventurePluginGameContext* GameContext, UInventoryItem* Item);

	/**
	* Retrieves the only instance of the requested item class. Necessary to access any functionality provided by the Item class. Always use this method, never instantiate UInventoryItem directly.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param Item The class whose instance is requested.
	* @return The only instance of this item.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Inventory")
	static UInventoryItem* GetItem(UAdventurePluginGameContext* GameContext, TSubclassOf<UInventoryItem> Item);

	/**
	* Retrieves the only instance of the requested character class. Neccessary to access any functionality provided by the Character class. Always use this method, never instantiate UAdventureCharacter directly.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param Character The class whose instance is requested.
	* @return The only instance of this character.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Character")
	static UAdventureCharacter* GetAdventureCharacter(UAdventurePluginGameContext* GameContext, TSubclassOf<UAdventureCharacter> Character);

	/**
	* Retrieves the default game context. Contains instances of classes defined in game config.
	* A game can choose a different way of getting a game context.
	* @see UAdventurePluginConfig
	* @param WorldObjectContext The object containing all data about the game world. Silently passed by Unreal Engine when possible.
	* @return The default game context.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin", meta = (WorldContext = WorldObjectContext))
	static UAdventurePluginGameContext* GetCurrentGameContext(UObject* WorldObjectContext);

private:
};
