#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_ItemBase.h"
#include "Inventory/InventoryItem.h"
#include "Inventory/InventoryItemBlueprint.h"
#include "InventoryController.h"
#include "ItemManager.h"
#include "AdventurePluginRuntime.h"
#include "AdventurePluginGameContext.h"
#include "DialogGraphNode_IfInInventory.generated.h"
/**
* This node is a branch node that can return a different next node based on whether a specified item is in inventory or not.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfInInventory : public UDialogGraphNode_ItemBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfInInventory()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "BranchingCategory", "Branching");
		ContextMenuName = FText::FromString("Branch on item in inventory");
#endif
	}
	/**
	* The next node if this node is true.
	*/
	UPROPERTY(BlueprintReadOnly)
		UDialogGraphNode* ChildTrue;
	/**
	* The next node if this node is false.
	*/
	UPROPERTY(BlueprintReadOnly)
		UDialogGraphNode* ChildFalse;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfInInventory", "NodeTitle", "IF {0} IN INVENTORY"),
			IsValid(Item) ? Item.GetDefaultObject()->Name : FText::FromString("<EMPTY>"));
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::White;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

#endif
	virtual void ResetSpecialChildren() override
	{
		ChildTrue = nullptr;
		ChildFalse = nullptr;
	}
	/**
	* Returns the next child based on whether this node is currently true (UDialogGraphNode_IsInInventory@see #ChildTrue) or false (UDialogGraphNode_IsInInventory@see #ChildFalse).
	* This node is true if the item specified in Item is true, @see UDialogGraphNode_ItemBase#Item
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The next node to be executed.
	*/
	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* GameContext) override
	{
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("DialogGraphNode_IfInInventory:GetNextNode")))
		{
			return nullptr;
		}
		if (!IsValid(Item))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_IfInInventory_GetNextNode_InvalidItem", "DialogGraphNode_IfInInventory:GetNextNode: Nil or invalid item passed."));
			return nullptr;
		}
		UInventoryItem* ItemInstance = GameContext->ItemManager->GetItem(Item);
		if (!IsValid(ItemInstance))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_IfInInventory_GetNextNode_InvalidItemInstance", "DialogGraphNode_IfInInventory:GetNextNode: Item could not be instantiated."));
			return nullptr;
		}
		return GameContext->InventoryController->GetInventory()->HasItem(ItemInstance, GameContext) ? ChildTrue: ChildFalse;
	}
};
