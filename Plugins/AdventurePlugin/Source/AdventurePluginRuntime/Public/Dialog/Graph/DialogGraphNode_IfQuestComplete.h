#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "BaseClasses/DialogGraphNode_TrueFalse.h"
#include "Quest/Graph/QuestGraph.h"
#include "DialogGraphNode_IfQuestComplete.generated.h"

/**
* This node is a branch node that can return a different next node if the quest UDialogGraphNode_IfQuestComplete#Quest is completed.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfQuestComplete : public UDialogGraphNode_TrueFalse
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfQuestComplete()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_IfQuestComplete_ContextName", "Branch on quest completion");
#endif
	}

	/**
	* Identifies the Quest that this node is about.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnQuestCompleteNode")
	UQuestGraph* Quest;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfQuestComplete", "NodeTitle", "IF {0} IS COMPLETE"),
			FText::FromString(IsValid(Quest) ? Quest->Name : TEXT("<EMPTY>")));
	}

#endif

	/**
	* This node is true if the quest UDialogGraphNode_IfQuestComplete#Quest is completed.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return False if the variable specification is invalid, otherwise value of that variable.
	*/
	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Quest))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_IfQuestComplete_IsTrue", "UDialogGraphNode_IfQuestComplete:IsTrue:Quest is null or invalid."));
			return false;
		}
		return Quest->IsComplete(GameContext, this);
	}
};
