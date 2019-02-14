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
	/*If true, it is possible to call Examine on this item.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Examination")
		bool bIsExaminable = true;
	/*If true, this item can be picked up from the scene.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
		bool bIsPickable = true;
	/*If true, this item has a use action that can be called, e.g. reading a map.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Usage")
		bool bIsUsable = false;
	/*The name of the use action of this item.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Usage")
		FText UseActionName;
	/*The type of the use action on this item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Usage")
		FName UseActionType;
	/*This notification will be fired when this item is picked up.*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory Item")
		FItemNotificationEvent OnAddedToInventory;
	/*This notification will be fired when this item is removed from inventory.*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory Item")
		FItemNotificationEvent OnRemovedFromInventory;
	/* Tags assigned to this item, e.g. weapon, critical, red herring etc. No inherent function unless designers make it so*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
		FGameplayTagContainer ItemTags;
	/*The examine action of this item.*/
	UFUNCTION(BlueprintNativeEvent, Category = "Adventure Plugin|Inventory")
		void Examine(UAdventurePluginGameContext* GameContext);
	/*The use action of this object.*/
	UFUNCTION(BlueprintNativeEvent, Category = "Adventure Plugin|Inventory")
		void Use(UAdventurePluginGameContext* GameContext);
	/*The icon representing this item in asset editor.*/
	virtual UTexture2D* GetIcon() const override
	{
		return Icon;
	}
	/*Returns true if this item was already picked up.*/
	UFUNCTION(BlueprintNativeEvent, Category = "Adventure Plugin|Inventory")
		bool WasPickedUp(UAdventurePluginGameContext* GameContext);

	/* The default state of the item, e.g. it is spawned, but not yet picked up. In defaults this is the inital state of the item.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Item")
		EInventoryItemState DefaultItemState;
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
		EInventoryItemState GetItemState(UAdventurePluginGameContext* GameContext);
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
		void SetItemState(EInventoryItemState NewValue, UAdventurePluginGameContext* GameContext);
};