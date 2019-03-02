#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "Inventory/InventoryItem.h"
#include "Inventory/InventoryItemBlueprint.h"
#include "InventoryController.h"
#include "ItemManager.h"
#include "AdventurePluginRuntime.h"
#include "DialogGraphNode_ItemBase.generated.h"

/**
* This node is a base class for items contain an inventory item as a parameter.
*/
UCLASS(Abstract, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_ItemBase : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_ItemBase()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "ItemsCategory", "Items");
#endif
	}

	/**
	* The relevant item.
	* In editor we are actually filling this through PickerItem, so we can see icons of the items.
	* @see UDialogGraphNode_IsInInventory#PickerItem
	*/
	UPROPERTY(BlueprintReadOnly, Category = "ItemNode")
	TSubclassOf<UInventoryItem> Item;

#if WITH_EDITORONLY_DATA

	/**
	* The relevant item.
	*/
	UPROPERTY(EditAnywhere, Category = "BranchOnItemNode", Meta = (DisplayName = "Item"))
	UInventoryItemBlueprint* PickerItem;

#endif
};
