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

	virtual bool IsSatisfied() override
	{
		return true; // TODO
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const override
	{
		return NSLOCTEXT("QuestGraphNode_End", "Title", "END");
	}

	virtual inline FLinearColor GetBackgroundColor() const override
	{
		return FLinearColor::White;
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

	virtual inline uint32 GetOutputPinsCount() const override
	{
		return 0;
	}

#endif
};
