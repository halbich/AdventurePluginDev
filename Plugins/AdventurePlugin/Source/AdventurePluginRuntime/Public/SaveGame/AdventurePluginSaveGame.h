#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Inventory/InventoryItemState.h"
#include "Inventory/InventoryItem.h"
#include "AdventurePluginSaveGame.generated.h"

/**
 * Contains all data that should be serialized to represent the game state.
 * Adventure Plugin automatically serializes all quest variables and flags, whether once node in dialogs where executed, inventory and inventory item states.
 * Everything else must be handled by the game itself.
 * <p>
 * The serialized variables of Adventure Plugin work directly with the instance of this class stored on the game context.
 * The serialized variables are not stored on those objects at all
 * so loading a new game is as easy as replacing the save game on context.
 * However, it is expected that the scene objects will probably have to be reloaded to represent that game state.
 * <p>
 * If you want to work with this object and use it for serialization of your own items, be careful to use unique names that will not clash with other variables.
 * It is unlikely to clash with the Adventure Plugin variables, as the quest variables include full path to the quest as a name, once nodes use generated UUIDs.
 * And inventory items and their states are stored separately, you should not have to interact with those.
 */
UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew)
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginSaveGame : public USaveGame
{
	GENERATED_BODY()
	UAdventurePluginSaveGame();

	/**
	* Contains all booleans stored in this save game.
	*/
	UPROPERTY(VisibleAnywhere, Category= "StoredValues")
	TMap<FName, bool> StorageBoolean;

	/**
	* Contains all integers stored in this save game.
	*/
	UPROPERTY(VisibleAnywhere, Category = "StoredValues")
	TMap<FName, int32> StorageInt;

	/**
	* Contains all strings stored in this save game.
	*/
	UPROPERTY(VisibleAnywhere, Category = "StoredValues")
	TMap<FName, FString> StorageString;

	/**
	* Contains all states of all items that have a state specified.
	*/
	UPROPERTY(VisibleAnywhere, Category = "StoredValues")
	TMap<TSubclassOf<UInventoryItem>, EInventoryItemState> StorageItemStates;

public:

	/**
	* Contains items currently in inventory.
	*/
	UPROPERTY(VisibleAnywhere, Category = "StoredValues")
	TArray<TSubclassOf<UInventoryItem>> StorageInventory;

	/**
	* The name of this save game.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic, meta = (DisplayName = "Slot Name"))
	FString SaveSlotName;

	/**
	* For some platforms, master user index to identify the user doing the saving..
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic, meta = (DisplayName="User Index"))
	int32 SaveUserIndex;

	/**
	* Retrieves the specific boolean variable, or the default value if the variable was not yet stored.
	* @param Name The name of the variable.
	* @param bDefaultValue The default value to return if the value was not found on the object.
	* @return The variable value, or the default value if the variable was not yet stored.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
	bool GetBoolOrDefault(FName Name, bool bDefaultValue);

	/**
	* Sets a value of a specific boolean variable.
	* @param Name The name of the variable.
	* @param bValue The new value of that variable.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
	void SetBool(FName Name, bool bValue);

	/**
	* Retrieves the specific integer variable, or the default value if the variable was not yet stored.
	* @param Name The name of the variable.
	* @param DefaultValue The default value to return if the value was not found on the object.
	* @return The variable value, or the default value if the variable was not yet stored.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
	int32 GetIntOrDefault(FName Name, int32 DefaultValue);

	/**
	* Sets a value of a specific integer variable.
	* @param Name The name of the variable.
	* @param Value The new value of that variable.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
	void SetInt(FName Name, int32 Value);

	/**
	* Retrieves the specific string variable, or the default value if the variable was not yet stored.
	* @param Name The name of the variable.
	* @param DefaultValue The default value to return if the value was not found on the object.
	* @return The variable value, or the default value if the variable was not yet stored.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
	FString GetStringOrDefault(FName Name, FString DefaultValue);

	/**
	* Sets a value of a specific string variable.
	* @param Name The name of the variable.
	* @param Value The new value of that variable.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
	void SetString(FName Name, FString Value);

	/**
	* Retrieves the state of the specific item, or the default value if the item state was not yet stored.
	* @param Item The item whose state is requested.
	* @param DefaultValue The default value to return if the value was not found on the object.
	* @return The item state, or the default value if the state was not yet stored.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
	EInventoryItemState GetItemStateOrDefault(TSubclassOf<UInventoryItem> Item, EInventoryItemState DefaultValue);

	/**
	* Sets the state of a specific item.
	* @param Item The item whose state should be changed.
	* @param Value The new state of the item.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
	void SetItemState(TSubclassOf<UInventoryItem> Item, EInventoryItemState Value);

	/**
	* Creates a new, empty save game with the specified arguments
	* @param SlotName The name of the save game slot.
	* @param UserIndex For some platforms, master user index to identify the user doing the saving.
	* @return The created save game.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
	static UAdventurePluginSaveGame* CreateSave(FString SlotName , int32 UserIndex);

	/**
	* Saves the data in this class to the disk.
	* @return True if the save was successful.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
	bool Save();
};
