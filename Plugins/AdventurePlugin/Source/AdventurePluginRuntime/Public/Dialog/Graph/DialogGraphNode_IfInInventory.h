#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "BaseClasses/DialogGraphNode_ItemBase.h"
#include "Inventory/InventoryItem.h"
#include "Inventory/InventoryItemBlueprint.h"
#include "Inventory/Controller/InventoryController.h"
#include "Inventory/ItemManager.h"
#include "AdventurePluginRuntime.h"
#include "Common/AdventurePluginGameContext.h"
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
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_IfInInventory_ContextName", "Branch on item in inventory");
#endif
	}

	/**
	* The next node if this node is true.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Adventure Plugin")
	UDialogGraphNode* ChildTrue;

	/**
	* The next node if this node is false.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Adventure Plugin")
	UDialogGraphNode* ChildFalse;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfInInventory", "NodeTitle", "IF {0} IN INVENTORY"),
			IsValid(Item) ? Item.GetDefaultObject()->Name : FText::FromString(TEXT("<EMPTY>")));
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
	* Returns the next child based on whether this node is currently true (UDialogGraphNode_IfInInventory#ChildTrue) or false (UDialogGraphNode_IfInInventory#ChildFalse).
	* This node is true if the item specified in UDialogGraphNode_ItemBase#Item is in inventory.
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
		return GameContext->InventoryController->GetInventory()->HasItem(ItemInstance, GameContext, this) ? ChildTrue: ChildFalse;
	}
};
