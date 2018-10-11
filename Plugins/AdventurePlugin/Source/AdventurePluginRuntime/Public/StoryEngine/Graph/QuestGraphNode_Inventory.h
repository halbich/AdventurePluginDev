#pragma once

#include "CoreMinimal.h"
#include "QuestGraphNode.h"
#include "Inventory/InventoryItem.h"
#include "QuestGraphNode_Inventory.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UQuestGraphNode_Inventory : public UQuestGraphNode
{
	GENERATED_BODY()

public:

	UQuestGraphNode_Inventory()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("QuestGraphNode_Inventory", "ContextMenuName", "Is in inventory");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphNode_Editor")
	UInventoryItem* Item;

	virtual bool IsSatisfied() override
	{
		return true; // TODO
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const override
	{
		return IsValid(Item) ? Item->Name : NSLOCTEXT("QuestGraphNode_Inventory", "EmptyItem", "<EMPTY>");
	}

	virtual inline FLinearColor GetBackgroundColor() const override
	{
		return FLinearColor::Blue;
	}

#endif
};
