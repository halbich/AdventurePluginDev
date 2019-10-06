#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "QuestGraphNode.h"
#include "Inventory/InventoryItem.h"
#include "Inventory/InventoryItemBlueprint.h"
#include "AdventurePluginRuntime.h"
#include "Inventory/Controller/InventoryController.h"
#include "Combinations/CombinableObjectManager.h"
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
	* The item this node represents. Once that item is picked up, this node becomes true.
	* In editor this is filled by UQuestGraphNode_Inventory#PickerItem, because its picker supports user-friendly asset thumbnails.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "InventoryItemNode")
	TSubclassOf<UInventoryItem> Item;

#if WITH_EDITORONLY_DATA

	/**
	* The helper property for filling UQuestGraphNode_Inventory#Item. It is used only in editor
	* because its picker supports user-friendly asset thumbnails.
	*/
	UPROPERTY(EditAnywhere, Category = "InventoryItemNode", Meta = (DisplayName = "Item"))
	UInventoryItemBlueprint* PickerItem;

#endif

	virtual bool IsTrue(UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext) override
	{
		auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("QuestGraphNode_Inventory:IsTrue")))
		{
			return false;
		}
		if (!IsValid(Item))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestGraphNode_Inventory_InvalidItem", "Quest graph node inventory:IsTrue: Nil or invalid item passed."));
			return false;
		}
		UInventoryItem* ItemInstance = Cast<UInventoryItem>(GameContext->CombinableObjectManager->GetCombinableObjectInstance(Item, WorldObjectContext));
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
