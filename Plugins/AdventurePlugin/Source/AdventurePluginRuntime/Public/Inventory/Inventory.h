 #pragma once

#include "Core.h"
#include "Inventory/InventoryItem.h"
#include "Inventory.generated.h"

/**
* Description for an event raised when something in inventory changes, an item is added or removed.
* @param ChangedItem The items being added or removed.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryChangedEvent, const TArray<UInventoryItem*>&, ChangedItems);

/**
* An inventory, i.e. a collection of items. 
* Each item can be only once in the inventory.
* This class is serializing the inventory into a save file and raises events when inventory changes, notifying the presenter to update itself.
*/
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UInventory : public UObject
{
	GENERATED_BODY()

public:

	/**
	* This event is raised when the inventory changes, i.e. an item is added or removed.
	* The event has a ChangedItem parameter specifying which item was changed.
	* Note that when multiple items are added or removed at once, the ChangedItem parameter will be null.
	* Also note that you can also subscribe to events on specific items themselves, they also have events fired when an item is added or removed from inventory.
	*/
	UPROPERTY(BlueprintAssignable, Category = "Adventure Plugin|Inventory")
	FInventoryChangedEvent InventoryChanged;

	/**
	* Retrieves all items currently in this inventory.
	* @return All items in the inventory.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
	virtual TArray<UInventoryItem*> GetItems(UAdventurePluginGameContext* GameContext);

	/**
	* Checks whether the specified item is in inventory.
	* @param Item The item in question.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if this item is in the inventory, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
	virtual bool HasItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContext);

	/**
	* Adds a specified item to the inventory.
	* @param Item The item to add.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
	virtual bool AddItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContext);

	/**
	* Removes a specified item from the inventory.
	* @param Item The item to remove.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if the item was successfully removed, so mainly true if the item actually was in the inventory.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
	virtual bool RemoveItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContext);

	/**
	* Call if multiple AddItem() and RemoveItem() calls will follow.
	* Will silence the UInventory#InventoryChanged until EndUpdate() is called.
	* EndUpdate() will then raise the UInventory#InventoryChanged event.
	* Exists mainly so UInventory#InventoryChanged event is not called multiple times when doing multiple inventory changes one after another.
	* @see UInventory#InventoryChanged
	* @see UInventory#EndUpdate
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
	virtual void BeginUpdate();

	/**
	* Call always after EndUpdate().
	* Will raise the UInventory#InventoryChanged event.
	* Exists mainly so UInventory#InventoryChanged event is not called multiple times when doing multiple inventory changes one after another.
	* @see UInventory#InventoryChanged
	* @see UInventory#BeginUpdate
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
	virtual void EndUpdate();

protected:

	/**
	* True if we are between BeginUpdate() and EndUpdate() calls.
	* UInventory#InventoryChanged event should be silenced.
	*/
	UPROPERTY(Transient)
	bool bIsUpdating;

	/**
	* This property stores the items that are being modified between BeginUpdate() and EndUpdate() calls.
	*/
	UPROPERTY(Transient)
	TArray<UInventoryItem*> ModifiedItems;

	/**
	* Replaces the entire inventory with a new set of items.
	* @param NewItems The items that should now be in the inventory.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
	virtual void SetItems(const TArray<UInventoryItem*>& NewItems, UAdventurePluginGameContext* GameContext);
};