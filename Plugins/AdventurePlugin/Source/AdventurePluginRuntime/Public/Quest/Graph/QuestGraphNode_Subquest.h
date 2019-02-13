#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphNode.h"
#include "AdventurePluginRuntime.h"
#include "QuestGraphNode_Subquest.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UQuestGraphNode_Subquest : public UQuestGraphNode
{
	GENERATED_BODY()

public:

	UQuestGraphNode_Subquest()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("QuestGraphNode_Subquest", "ContextMenuName", "Subquest");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SubquestNode")
	UQuestGraph* Subquest;

	virtual bool IsSatisfied(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Subquest))
		{
			LOG_Warning(NSLOCTEXT("AP", "Invalid Subquest", "Quest graph node: Subquest: Nil or invalid Subquest passed"));
			return false;
		}
		return Subquest->EndNode->IsSatisfied(GameContext);
	}

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
