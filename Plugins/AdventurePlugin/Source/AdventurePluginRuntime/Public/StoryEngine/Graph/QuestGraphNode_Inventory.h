#pragma once

#include "CoreMinimal.h"
#include "QuestGraphNode.h"
#include "QuestGraphNode_Inventory.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UQuestGraphNode_Inventory : public UQuestGraphNode
{
	GENERATED_BODY()

public:

	UQuestGraphNode_Inventory()
	{
		ContextMenuName = NSLOCTEXT("QuestGraphNode_Inventory", "ContextMenuName", "Is in inventory");
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphNode_Editor")
	FName ItemName;

	virtual bool IsSatisfied() override
	{
		return true; // TODO
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const override
	{
		return FText::FromName(ItemName);
	}

	virtual void SetNodeTitle(const FText & NewTitle) override
	{
		ItemName = FName(*NewTitle.ToString());
	}

	virtual inline FLinearColor GetBackgroundColor() const override
	{
		return FLinearColor::Blue;
	}

	virtual inline bool CanRename() const override
	{
		return true;
	}

#endif
};
