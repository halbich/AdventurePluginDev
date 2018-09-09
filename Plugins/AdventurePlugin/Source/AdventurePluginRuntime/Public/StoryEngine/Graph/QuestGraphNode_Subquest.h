#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphNode.h"
#include "QuestGraphNode_Subquest.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UQuestGraphNode_Subquest : public UQuestGraphNode
{
	GENERATED_BODY()

public:

	UQuestGraphNode_Subquest()
	{
		ContextMenuName = NSLOCTEXT("QuestGraphNode_Subquest", "ContextMenuName", "Subquest");
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphNode_Editor")
	UQuestGraph* Subquest;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return IsValid(Subquest) ? FText::FromString(Subquest->Name) : NSLOCTEXT("QuestGraphNode_Subquest", "EmptySubquest", "<EMPTY>");
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor(0, 1, 1);
	}

#endif
};
