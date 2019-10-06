#pragma once

#include "CoreMinimal.h"
#include "UObject/TextProperty.h" 
#include "Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Delegates/Delegate.h"
#include "InteractableSceneObject.h"
#include "Dialog/Structs/DialogGraphEntryPoint.h"
#include "Inventory/Structs/UseActionType.h"
#include "Inventory/InventoryItemState.h"
#include "InventoryItem.generated.h"

class UInventoryItemBlueprint;
class UInventory;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemNotificationEvent, UInventoryItem*, AffectedItem);

/**
* Represents a single game item.
* This class should specify all data and behavior of an item that does not depend on its placement in the scene. Its name, actions, etc.
* It is expected that the designer will create a subclass of this class for each item and then also create a separate blueprint to handle the item's behavior on the scene.
* To allow combinations to work correctly, subclasses of this class should be done only in blueprints.
* The state of the item is serialized automatically.
*/
UCLASS(Abstract, BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UInventoryItem : public UInteractableSceneObject, public IIconThumbnailInterface
{
	GENERATED_BODY()

public:

	/**
	* The inventory icon representing this item.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
	UTexture2D* Icon;

	/**
	* If true, it is possible to pick up this item from scene. This is a value returned by IsPickable() if not overriden.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
	bool bDefaultIsPickable = true;

	/**
	* Checks whether this item can be picked up right now.
	* Unless overriden this method returns UInventoryItem#bDefaultIsPickable.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if the item can be picked up right now, otherwise false.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory", meta = (AdvancedDisplay = GameContextOverride))
	bool IsPickable(UAdventurePluginGameContext* GameContextOverride);

	/**
	* The initial state of the item.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
	EInventoryItemState DefaultItemState;

	/**
	* Retrieves the current state of the item.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The current state of the item.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory", meta = (AdvancedDisplay = GameContextOverride))
	EInventoryItemState GetItemState(UAdventurePluginGameContext* GameContextOverride);

	/**
	* Changes the state of the item. Is serialized.
	* @param NewValue The new state of the item.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory", meta = (AdvancedDisplay = GameContextOverride))
	void SetItemState(EInventoryItemState NewValue, UAdventurePluginGameContext* GameContextOverride);

	/**
	* This event is fired when the item's state has changed.
	*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory Item")
	FItemNotificationEvent ItemStateChanged;

	/**
	* This event will be fired when this item is added to inventory.
	*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory Item")
	FItemNotificationEvent AddedToInventory;

	/**
	* This method is called when the item is added to inventory. Expected to be overriden on child classes to give custom behavior.
	* @param Inventory The inventory to which this item was added.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Adventure Plugin|Inventory", meta = (AdvancedDisplay = GameContextOverride))
	void OnAddedToInventory(UInventory* Inventory, UAdventurePluginGameContext* GameContextOverride);

	/**
	* This event will be fired when this item is removed from inventory.
	*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory Item")
	FItemNotificationEvent RemovedFromInventory;

	/**
	* This method is called when the item is removed from inventory. Expected to be overriden on child classes to give custom behavior.
	* @param Inventory The inventory from which this item was removed.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Adventure Plugin|Inventory", meta = (AdvancedDisplay = GameContextOverride))
	void OnRemovedFromInventory(UInventory* Inventory, UAdventurePluginGameContext* GameContextOverride);

	/**
	* Returns the icon representing this item in asset editor.
	* @return The asset editor icon of this item.
	*/
	virtual UTexture2D* GetIcon() const override
	{
		return Icon;
	}

	/**
	* Returns true if this item was already picked up.
	* Default behavior checks the item state using GetItemState() to see if the item was already picked up. 
	* Can be overriden if the item uses custom states.
	* @return True if the item was already picked up.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory", meta = (AdvancedDisplay = GameContextOverride))
	bool WasPickedUp(UAdventurePluginGameContext* GameContextOverride);
};