#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphNode.h"
#include "QuestGraphNode_End.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UQuestGraphNode_End : public UQuestGraphNode
{
	GENERATED_BODY()

public:

	UQuestGraphNode_End()
	{
		ContextMenuName = NSLOCTEXT("QuestGraphNode_End", "ContextMenuName", "End Point");
	}

	virtual ~UQuestGraphNode_End()
	{
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return NSLOCTEXT("QuestGraphNode_End", "Title", "END");
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::White;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

	virtual inline bool CanAdd() const override
	{
		return false;
	}

	virtual inline bool CanDelete() const override
	{
		return false;
	}

	virtual inline bool CanDuplicate() const override
	{
		return false;
	}

#endif
};
