#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode_LessEqualMoreBase.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphInteger.h"
#include "DialogGraphNode_IfInteger.generated.h"

/**
* This node is a branch node that can return a different next node based on a value of an integer variable on a quest.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfInteger : public UDialogGraphNode_LessEqualMoreBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfInteger()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Branch on integer variable comparison with a constant");
#endif
	}

	/**
	* Identifies the variable this node is working with.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnIntegerNode")
	FQuestGraphInteger Integer;

	/**
	* The constant value with which we are comparing in this node.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnIntegerNode")
	int32 Constant;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfInteger", "NodeTitle", "COMPARE {0}->{1} WITH {2}"),
			FText::FromString(IsValid(Integer.Quest) ? Integer.Quest->Name : "<EMPTY>"),
			FText::FromName(Integer.IntegerName),
			Constant);
	}
#endif

	/**
	* Returns the next node to be executed, based on the value of the relevant integer variable and constant,
	* whether the variable UDialogGraphNode_IfInteger#Integer is less, more or equal than the constant UDialogGraphNode_IfInteger#Constant.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Null if the variable identification is not valid, otherwise the next child to be executed.
	*/
	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Integer.Quest))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_IfInteger_GetNextNode", "DialogGraphNode_IfInteger:GetNextNode:Quest is null or invalid."));
			return nullptr;
		}
		int32 VariableValue = Integer.Quest->GetInteger(GameContext, Integer.IntegerName);
		if (VariableValue < Constant)
		{
			return ChildLess;
		}
		else if (VariableValue == Constant)
		{
			return ChildEqual;
		}
		else
		{
			return ChildMore;
		}
	}
};
