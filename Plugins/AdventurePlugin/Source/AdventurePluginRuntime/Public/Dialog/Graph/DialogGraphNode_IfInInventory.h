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

	UPROPERTY(BlueprintReadOnly, Category = "BranchOnItemNode")
		TSubclassOf<UInventoryItem> Item;

#if WITH_EDITORONLY_DATA

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

	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("DialogGraphNode_IfInInventory:IsTrue")))
		{
			return false;
		}
		if (!IsValid(Item))
		{
			LOG_Warning(NSLOCTEXT("AP", "Invalid Item", "Quest graph node: Inventory: Nil or invalid item passed"));
			return false;
		}
		UInventoryItem* ItemInstance = GameContext->ItemManager->GetItem(Item);
		if (!IsValid(ItemInstance))
		{
			LOG_Warning(NSLOCTEXT("AP", "Invalid Item Instance", "Quest graph node: Item could not be instantiated"));
			return false;
		}
		return GameContext->InventoryController->GetInventory()->HasItem(ItemInstance, GameContext);
	}
};
