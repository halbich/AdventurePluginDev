#pragma once

#include "CoreMinimal.h"
#include "QuestGraphNode.h"
#include "QuestGraphNode_Comment.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UQuestGraphNode_Comment : public UQuestGraphNode
{
	GENERATED_BODY()

public:

	UQuestGraphNode_Comment()
	{
		ContextMenuName = NSLOCTEXT("QuestGraphNode_Comment", "ContextMenuName", "Comment");
	}

	UPROPERTY(EditAnywhere, Category = "QuestGraphNode_Editor")
	FText Text;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const override
	{
		return Text;
	}

	virtual inline FLinearColor GetBackgroundColor() const override
	{
		return FLinearColor(1, 0, 1);
	}

#endif
};
