#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "Inventory/InventoryItem.h"
#include "InventoryController.h"
#include "DialogGraphNode_IfInInventory.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfInInventory : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfInInventory()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Branch on item in inventory");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
		UInventoryItem* Item;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfInInventory", "NodeTitle", "If \"{0}\" is in inventory"),
			Item != nullptr && Item->IsValidLowLevel() ? Item->Name : FText::FromString("<EMPTY>"));
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

	virtual uint32 GetOutputPinsCount() const override
	{
		return 2;
	}

	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* context) override
	{
		bool hasItem = context->InventoryController->GetInventory()->HasItem(Item);
		int32 bin = hasItem ? 0 : 1;
		return Cast<UDialogGraphNode>(GetFirstChildInBin(bin));
	}
};
