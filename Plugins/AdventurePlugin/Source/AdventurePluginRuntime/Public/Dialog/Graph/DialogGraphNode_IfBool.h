#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphBool.h"
#include "DialogGraphNode_IfBool.generated.h"

/**
* This node is a branch node that can return a different next node based on a value
* of a bool variable UDialogGraphNode_IfBool#Bool on a quest.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfBool : public UDialogGraphNode_TrueFalse
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfBool()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_IfBool_ContextName", "Branch on bool variable.");
#endif
	}

	/**
	* Identifies the variable this node is working with.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnBoolNode")
	FQuestGraphBool Bool;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfBool", "NodeTitle", "IF {0}->{1}"),
			FText::FromString(IsValid(Bool.Quest) ? Bool.Quest->Name : "<EMPTY>"),
			FText::FromName(Bool.BoolName));
	}

#endif

	/**
	* This node is true if the variable UDialogGraphNode_IfBool#Bool is true.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return False if the variable specification is invalid, otherwise value of that variable.
	*/
	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Bool.Quest))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_IfBool_IsTrue", "DialogGraphNode_IfBool:IsTrue:Quest is null or invalid."));
			return false;
		}
		return Bool.Quest->GetBool(GameContext, Bool.BoolName);
	}
};
