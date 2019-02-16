#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.h"
#include "Inventory/InventoryItem.h"
#include "Inventory/InventoryItemBlueprint.h"
#include "InventoryController.h"
#include "ItemManager.h"
#include "AdventurePluginRuntime.h"
#include "DialogGraphNode_IfInInventory.generated.h"
/**
* This node is a branch node that can return a different next node based on whether a specified item is in inventory or not.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfInInventory : public UDialogGraphNode_TrueFalse
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfInInventory()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Branch on item in inventory");
#endif
	}
	/**
	* The class of the item that we are asking about.
	* In editor we are actually filling this through PickerItem, so we can see icons of the items. @see UDialogGraphNode_IsInInventory#PickerItem
	*/
	UPROPERTY(BlueprintReadOnly, Category = "BranchOnItemNode")
	TSubclassOf<UInventoryItem> Item;

#if WITH_EDITORONLY_DATA
	/**
	* The item this nodes represents.
	*/
	UPROPERTY(EditAnywhere, Category = "BranchOnItemNode", Meta = (DisplayName = "Item"))
	UInventoryItemBlueprint* PickerItem;

#endif

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfInInventory", "NodeTitle", "IF {0} IN INVENTORY"),
			IsValid(Item) ? Item.GetDefaultObject()->Name : FText::FromString("<EMPTY>"));
	}

#endif
	/**
	* This node is true if the item specified in Item is true, @see UDialogGraphNode_IsInInventory#Item
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return False if either the GameContext or Item is invalid or not in inventory. Otherwise true.
	*/
	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("DialogGraphNode_IfInInventory:IsTrue")))
		{
			return false;
		}
		if (!IsValid(Item))
		{
			LOG_Warning(NSLOCTEXT("AP", "DialogGraphNode_IfInInventoryInvalidItem", "DialogGraphNode_IfInInventory:IsTrue: Nil or invalid item passed"));
			return false;
		}
		UInventoryItem* ItemInstance = GameContext->ItemManager->GetItem(Item);
		if (!IsValid(ItemInstance))
		{
			LOG_Warning(NSLOCTEXT("AP", "DialogGraphNode_IfInInventoryInvalidItemInstance", "DialogGraphNode_IfInInventory:IsTrue: Item could not be instantiated"));
			return false;
		}
		return GameContext->InventoryController->GetInventory()->HasItem(ItemInstance, GameContext);
	}
};
