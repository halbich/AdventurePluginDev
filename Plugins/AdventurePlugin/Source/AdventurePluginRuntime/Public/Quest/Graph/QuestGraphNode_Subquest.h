#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphNode.h"
#include "AdventurePluginRuntime.h"
#include "QuestGraphNode_Subquest.generated.h"
/**
* This node points to some other quest and is true if that quest is true.
*/
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

	/**
	* The quest that must be true for this node to be true.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SubquestNode")
	UQuestGraph* Subquest;

	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Subquest))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestGraphNode_Subquest_InvalidSubquest", "Quest graph node Subquest:IsTrue: Nil or invalid Subquest passed"));
			return false;
		}
		return Subquest->IsComplete(GameContext);
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
