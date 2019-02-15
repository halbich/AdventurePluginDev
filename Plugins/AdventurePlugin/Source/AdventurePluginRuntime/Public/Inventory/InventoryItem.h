#pragma once

#include "Core.h"
#include "TextProperty.h" 
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Delegate.h"
#include "SimpleCombination.h"
#include "CombinationInterface.h"
#include "CombinableObject.h"
#include "Dialog/Structs/DialogGraphEntryPoint.h"
#include "InventoryItemState.h"
#include "InventoryItem.generated.h"

class UInventoryItemBlueprint;
class UInventory;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemNotificationEvent, UInventoryItem*, AffectedItem);
/*Represents a single game item.*/
UCLASS(Abstract, BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UInventoryItem : public UCombinableObject, public IIconThumbnailInterface
{
	GENERATED_BODY()

public:
	/*The name of this item that should be displayed to the user.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
		FText Name;
	/*The inventory icon representing this image.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
		UTexture2D* Icon;
	/*The dialog that should be launched when this item is examined.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Examination")
		FDialogGraphEntryPoint ExamineDialog;
	/* Tags assigned to this item, e.g. weapon, critical, red herring etc. No inherent function unless designers make it so*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
		FGameplayTagContainer ItemTags;

	/*If true, it is possible to call Examine on this item. This is a value returned by IsExaminable if not overriden.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Examination")
		bool bDefaultIsExaminable = true;
	/* Returns true if the item can be examined right now. By default returns true if bDefaultIsExaminable is true.*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory")
		bool IsExaminable(UAdventurePluginGameContext* GameContext);
	/*If true, this item can be picked up from the scene. This is a value returned by IsPickable if not overriden.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
		bool bDefaultIsPickable = true;
	/* Returns true if the item can be picked up right now. Can be overriden, by default returns true if bDefaultIsPickable is true and the item is not in inventory.*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory")
		bool IsPickable(UAdventurePluginGameContext* GameContext);
	/*If true, this item has a use action that can be called, e.g. reading a map. This is a value returned by IsUsable if not overriden.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Usage")
		bool bDefaultIsUsable = false;
	/* Returns true if the can be used right now. Can be overriden, by default returns true if bDefaultIsUsable is true.*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory")
		bool IsUsable(UAdventurePluginGameContext* GameContext);

	/*The name of the use action of this item.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Usage")
		FText UseActionName;
	/*The type of the use action on this item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Usage")
		FName UseActionType;

	/* The default state of the item, e.g. it is spawned, but not yet picked up. In defaults this is the inital state of the item.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
		EInventoryItemState DefaultItemState;
	/*Retrieves the current state of the item.*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
		EInventoryItemState GetItemState(UAdventurePluginGameContext* GameContext);
	/*Sets the current state of the item*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
		void SetItemState(EInventoryItemState NewValue, UAdventurePluginGameContext* GameContext);

	/*This notification will be fired when this item is added to inventory.*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory Item")
		FItemNotificationEvent AddedToInventory;
	/*This method is called when the item is added to inventory. Expected to be overriden on child classes to give custom behavior.*/
	UFUNCTION(BlueprintNativeEvent, Category = "Adventure Plugin|Inventory")
		void OnAddedToInventory(UInventory* Inventory, UAdventurePluginGameContext* GameContext);

	/*This notification will be fired when this item is removed from inventory.*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory Item")
		FItemNotificationEvent RemovedFromInventory;
	/*This method is called when the item is removed from inventory. Expected to be overriden on child classes to give custom behavior.*/
	UFUNCTION(BlueprintNativeEvent, Category = "Adventure Plugin|Inventory")
		void OnRemovedFromInventory(UInventory* Inventory, UAdventurePluginGameContext* GameContext);

	/*Executes examine action on the item. Can be overriden, default behavior starts the examine dialog.*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory")
		void Examine(UAdventurePluginGameContext* GameContext);
	/*Executes the use action of the object. Does nothing by default.*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory")
		void Use(UAdventurePluginGameContext* GameContext);

	/*The icon representing this item in asset editor.*/
	virtual UTexture2D* GetIcon() const override
	{
		return Icon;
	}
	/*Returns true if this item was already picked up.*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Inventory")
		bool WasPickedUp(UAdventurePluginGameContext* GameContext);
};