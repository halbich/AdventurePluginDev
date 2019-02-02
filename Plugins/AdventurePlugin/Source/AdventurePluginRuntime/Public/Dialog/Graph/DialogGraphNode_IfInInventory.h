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
			Item != nullptr && Item->IsValidLowLevel() ? Item.GetDefaultObject()->Name : FText::FromString("<EMPTY>"));
	}

#endif

	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (GameContext == NULL || !GameContext->IsValidLowLevel() ||
			GameContext->InventoryController == NULL || !GameContext->InventoryController->IsValidLowLevel() ||
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
		return GameContext->InventoryController->GetInventory()->HasItem(itemInstance);
	}
};