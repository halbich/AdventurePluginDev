#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "BaseClasses/DialogGraphNode_ItemBase.h"
#include "Inventory/Controller/InventoryController.h"
#include "Combinations/CombinableObjectManager.h"
#include "AdventurePluginRuntime.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode_AddToInventory.generated.h"

/**
* This node adds a specified item to the default inventory.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_AddToInventory : public UDialogGraphNode_ItemBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_AddToInventory()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_AddToInventory_ContextName", "Add item to inventory");
#endif
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfInInventory", "NodeTitle", "ADD {0} TO INVENTORY"),
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
	* Adds the specified item to the default inventory.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Always true. We should never halt execution.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("UDialogGraphNode_AddToInventory:Execute")))
		{
			return false;
		}
		if (!IsValid(Item))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_AddToInventory_Execute_InvalidItem", "DialogGraphNode_AddToInventory:Execute: Nil or invalid item passed"));
			return false;
		}
		UInventoryItem* ItemInstance = Cast<UInventoryItem>(GameContext->CombinableObjectManager->GetCombinableObjectInstance(Item, this));
		if (!IsValid(ItemInstance))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_AddToInventory_Execute_InvalidItemInstance", "DialogGraphNode_AddToInventory:Execute: Item could not be instantiated"));
			return false;
		}
		GameContext->InventoryController->GetInventory()->AddItem(ItemInstance, GameContext, this);
		return true;
	}
};
