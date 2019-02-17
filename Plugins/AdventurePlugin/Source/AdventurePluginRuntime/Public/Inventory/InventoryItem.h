#pragma once

#include "Core.h"
#include "TextProperty.h" 
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Delegate.h"
#include "CombinationInterface.h"
#include "CombinableObject.h"
#include "Dialog/Structs/DialogGraphEntryPoint.h"
#include "Inventory/Structs/UseActionType.h"
#include "InventoryItemState.h"
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
class ADVENTUREPLUGINRUNTIME_API UInventoryItem : public UCombinableObject, public IIconThumbnailInterface
{
	GENERATED_BODY()

public:
	/**
	* The name of this item that should be displayed to the player.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
		FText Name;
	/**
	* The inventory icon representing this item.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
		UTexture2D* Icon;
	/**
	* The dialog that should be started when this item is examined.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Examination")
		FDialogGraphEntryPoint ExamineDialog;
	/**
	* Tags assigned to this item, e.g. weapon, critical, red herring etc. 
	* No inherent function unless designers make it so.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
		FGameplayTagContainer ItemTags;

	/**
	* If true, it is possible examine on this item. This is a value returned by IsExaminable if not overriden. @see UInventoryItem#IsExaminable
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Examination")
		bool bDefaultIsExaminable = true;
	/**
	* Checks whether this item can be examined right now.
	* Unless overriden this method returns bDefaultIsExaminable. @see UInventoryItem#bDefaultIsExaminable
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if the item can be examined right now, otherwise false.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory")
		bool IsExaminable(UAdventurePluginGameContext* GameContext);
	/**
	* If true, it is possible to pick up this item from scene. This is a value returned by IsPickable if not overriden. @see UInventoryItem#IsPickable
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
		bool bDefaultIsPickable = true;
	/**
	* Checks whether this item can be picked up right now.
	* Unless overriden this method returns bDefaultIsPickable. @see UInventoryItem#bDefaultIsPickable
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if the item can be picked up right now, otherwise false.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory")
		bool IsPickable(UAdventurePluginGameContext* GameContext);
	/**
	* If true, this item has a use action that can be called, e.g. reading a map. This is a value returned by IsUsable if not overriden. @see UInventoryItem#IsUsable
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Usage")
		bool bDefaultIsUsable = false;
	/**
	* Checks whether this item can be used right now, i.e. it is possible to call Use method. @see UInventoryItem#Use
	* Unless overriden this method returns bDefaultIsUsable. @see UInventoryItem#bDefaultIsPickable
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if the item can be used right now, otherwise false.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory")
		bool IsUsable(UAdventurePluginGameContext* GameContext);

	/**
	* The name of the use action that can be displayed to the user, e.g. "Read a map".
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Usage")
		FText UseActionName;
	/**
	* The type of the use action, e.g. Use/Talk/Combine etc. @see UAdventurePluginConfig@ActionTypes
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Usage")
		FUseActionType UseActionType;

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
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
		EInventoryItemState GetItemState(UAdventurePluginGameContext* GameContext);
	/**
	* Changes the state of the item. Is serialized.
	* @param NewValue The new state of the item.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
		void SetItemState(EInventoryItemState NewValue, UAdventurePluginGameContext* GameContext);

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
	UFUNCTION(BlueprintNativeEvent, Category = "Adventure Plugin|Inventory")
		void OnAddedToInventory(UInventory* Inventory, UAdventurePluginGameContext* GameContext);

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
	UFUNCTION(BlueprintNativeEvent, Category = "Adventure Plugin|Inventory")
		void OnRemovedFromInventory(UInventory* Inventory, UAdventurePluginGameContext* GameContext);

	/**
	* Executes examine action on the item. Can be overriden, default behavior starts the examine dialog.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory")
		void Examine(UAdventurePluginGameContext* GameContext);
	/**
	* Executes the use action of the object. Can be overriden, does nothing by default.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory")
		void Use(UAdventurePluginGameContext* GameContext);

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
	* Default behavior checks the ItemState to see if the item was already picked up. See UInventoryItem#GetItemState
	* Can be overriden if the item uses custom states.
	* @return True if the item was already picked up.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory")
		bool WasPickedUp(UAdventurePluginGameContext* GameContext);
};