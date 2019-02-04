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

	UPROPERTY(BlueprintReadOnly, Category = "InventoryItemNode")
	TSubclassOf<UInventoryItem> Item;

#if WITH_EDITORONLY_DATA

	UPROPERTY(EditAnywhere, Category = "InventoryItemNode", Meta = (DisplayName = "Item"))
	UInventoryItemBlueprint* PickerItem;

#endif

	virtual bool IsSatisfied(UAdventurePluginGameContext* GameContext) override
	{
		if (GameContext == NULL || !GameContext->IsValidLowLevel() ||
			GameContext->ItemManager == NULL || !GameContext->ItemManager->IsValidLowLevel())
		{
			LOG_Error(NSLOCTEXT("AP", "Invalid Inventory Game context", "Quest graph node: Inventory: Invalid context passed"));
			return false;
		}
		if (Item == NULL || !Item->IsValidLowLevel())
		{
			LOG_Warning(NSLOCTEXT("AP", "Invalid Item", "Quest graph node: Inventory: Nil or invalid item passed"));
			return false;
		}
		auto* itemInstance = GameContext->ItemManager->GetItem(Item);
		if (itemInstance == nullptr || !itemInstance->IsValidLowLevel())
		{
			LOG_Warning(NSLOCTEXT("AP", "Invalid Item Instance", "Quest graph node: Item could not be instantiated"));
			return false;
		}
		return itemInstance->WasPickedUp();
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
