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

	virtual inline FText GetNodeTitle() const
	{
		return Text;
	}

	virtual void SetNodeTitle(const FText & NewTitle)
	{

	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor(1, 0, 1);
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

#endif
};
