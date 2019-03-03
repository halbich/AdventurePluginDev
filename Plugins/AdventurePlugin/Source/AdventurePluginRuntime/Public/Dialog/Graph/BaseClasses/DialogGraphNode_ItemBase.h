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
* This node is a base class for nodes containing an inventory item as a parameter.
* @see FDialogInventoryItemCustomization
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
	* In editor this is filled by UDialogGraphNode_ItemBase#PickerItem, because its picker supports user-friendly asset thumbnails.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "ItemNode")
	TSubclassOf<UInventoryItem> Item;

#if WITH_EDITORONLY_DATA

	/**
	* The helper property for filling UDialogGraphNode_ItemBase#Item. It is used only in editor
	* because its picker supports user-friendly asset thumbnails.
	*/
	UPROPERTY(EditAnywhere, Category = "BranchOnItemNode", Meta = (DisplayName = "Item"))
	UInventoryItemBlueprint* PickerItem;

#endif
};
