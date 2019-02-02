#pragma once

#include "Core.h"
#include "TextProperty.h" 
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Delegate.h"
#include "SimpleCombination.h"
#include "CombinationInterface.h"
#include "CombinableObject.h"
#include "Dialogue/Structs/DialogGraphEntryPoint.h"
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
		FText Name;
	/*The inventory icon representing this image.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
		UTexture2D* Icon;
	/*The dialog that should be launched when this item is examined.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
		FDialogGraphEntryPoint ExamineDialog;
	/*If true, it is possible to call Examine on this item.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
		bool bIsExaminable = true;
	/*If true, this item can be picked up from the scene.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
		bool bIsPickable = true;
	/*If true, this item has a use action that can be called, e.g. reading a map.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
		bool bIsUsable = false;
	/*The name of the use action of this item.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
		FText UseActionName;
	// TODO: Create nice picker.
	/*The type of the use action on this item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
		FName UseActionType;
	/*This notification will be fired when this item is picked up.*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory")
		FItemNotificationEvent OnAddedToInventory;
	/*This notification will be fired when this item is removed from inventory.*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory")
		FItemNotificationEvent OnRemovedFromInventory;
	/* Tags assigned to this item, e.g. weapon, critical, red herring etc. No inherent function unless designers make it so*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
		FGameplayTagContainer ItemTags;
	/* The current state of the item, e.g. it is spawned, but not yet picked up. In defaults this is the inital state of the item.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		EInventoryItemState ItemState;
	/*The examine action of this item.*/
	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
		void Examine(UAdventurePluginGameContext* Context);
	/*The use action of this object.*/
	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
		void Use(UAdventurePluginGameContext* Context);
	/*The icon representing this item in asset editor.*/
	virtual UTexture2D* GetIcon() const override
	{
		return Icon;
	}
	/*Returns true if this item was already picked up.*/
	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
		bool WasPickedUp();
};