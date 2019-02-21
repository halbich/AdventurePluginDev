#pragma once

#include "CoreMinimal.h"
#include "AdventurePluginGameContext.h"
#include "QuestGraphNode.h"
#include "Inventory/InventoryItem.h"
#include "Inventory/InventoryItemBlueprint.h"
#include "AdventurePluginRuntime.h"
#include "InventoryController.h"
#include "ItemManager.h"
#include "QuestGraphNode_Inventory.generated.h"

/**
* Checks whether the specific item was already picked up.
* We check whether it was picked up instead of it is in inventory so it is still true that a node can be set to true and never becomes false.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UQuestGraphNode_Inventory : public UQuestGraphNode
{
	GENERATED_BODY()

public:

	UQuestGraphNode_Inventory()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("QuestGraphNode_Inventory", "ContextMenuName", "Picked up inventory item");
#endif
	}
	/**
	* The item we are checking for.
	* In editor this is filled by PickerItem. That is done so we have a nice picker. @see UQuestGraphNode#PickerItem
	*/
	UPROPERTY(BlueprintReadOnly, Category = "InventoryItemNode")
	TSubclassOf<UInventoryItem> Item;

#if WITH_EDITORONLY_DATA
	/**
	* The item this node represents. Once that item is picked up, this node becomes true.
	*/
	UPROPERTY(EditAnywhere, Category = "InventoryItemNode", Meta = (DisplayName = "Item"))
	UInventoryItemBlueprint* PickerItem;

#endif

	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("QuestGraphNode_Inventory:IsTrue")))
		{
			return false;
		}
		if (!IsValid(Item))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestGraphNode_Inventory_InvalidItem", "Quest graph node inventory:IsTrue: Nil or invalid item passed."));
			return false;
		}
		UInventoryItem* ItemInstance = GameContext->ItemManager->GetItem(Item);
		if (!IsValid(ItemInstance))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestGraphNode_Inventory_InvalidItemInstance", "Quest graph node inventory:IsTrue: Item could not be instantiated."));
			return false;
		}
		return ItemInstance->WasPickedUp(GameContext);
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const override
	{
		return IsValid(Item) ? Item.GetDefaultObject()->Name : NSLOCTEXT("QuestGraphNode_Inventory", "EmptyItem", "<EMPTY>");
	}

	virtual inline FLinearColor GetBackgroundColor() const override
	{
		return FLinearColor::Blue;
	}

#endif
};
