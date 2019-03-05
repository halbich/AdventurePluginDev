#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_ItemBase.h"
#include "InventoryController.h"
#include "ItemManager.h"
#include "AdventurePluginRuntime.h"
#include "AdventurePluginGameContext.h"
#include "DialogGraphNode_RemoveFromInventory.generated.h"

/**
* This node removes the specified inventory item from inventory if it is there.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_RemoveFromInventory : public UDialogGraphNode_ItemBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_RemoveFromInventory()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_RemoveFromInventory_ContextName", "Remove item from inventory");
#endif
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfInInventory", "NodeTitle", "REMOVE {0} FROM INVENTORY"),
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

	/**
	* Removes the specified item to the default inventory.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Always true. We should never halt execution.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("UDialogGraphNode_RemoveFromInventory:Execute")))
		{
			return false;
		}
		if (!IsValid(Item))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_RemoveFromInventory_Execute_InvalidItem", "DialogGraphNode_RemoveFromInventory:Execute: Nil or invalid item passed."));
			return false;
		}
		UInventoryItem* ItemInstance = GameContext->ItemManager->GetItem(Item);
		if (!IsValid(ItemInstance))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_RemoveFromInventory_Execute_InvalidItemInstance", "DialogGraphNode_RemoveFromInventory:Execute: Item could not be instantiated."));
			return false;
		}
		GameContext->InventoryController->GetInventory()->RemoveItem(ItemInstance, GameContext);
		return true;
	}
};
