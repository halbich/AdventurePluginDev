#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode_LessEqualMoreBase.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphInteger.h"
#include "DialogGraphNode_IfIntegerVariable.generated.h"

/**
* This node is a branch node that can return a different next node based on a value of an integer variable on a quest and its equality/inequality with another variable.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfIntegerVariable : public UDialogGraphNode_LessEqualMoreBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfIntegerVariable()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Branch on integer variable comparison with a variable");
#endif
	}

	/**
	* Identifies the first variable being compared.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnIntegerNode")
	FQuestGraphInteger FirstInteger;

	/**
	* Identifies the second variable being compared.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnIntegerNode")
	FQuestGraphInteger SecondInteger;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfIntegerVariable", "NodeTitle", "COMPARE {0}->{1} WITH {2}->{3}"),
			FText::FromString(IsValid(FirstInteger.Quest) ? FirstInteger.Quest->Name : "<EMPTY>"),
			FText::FromName(FirstInteger.IntegerName),
			FText::FromString(IsValid(SecondInteger.Quest) ? SecondInteger.Quest->Name : "<EMPTY>"),
			FText::FromName(SecondInteger.IntegerName));
	}

#endif

	/**
	* Returns the next node to be executed, based on the value of the relevant integer variables,
	* whether the variable UDialogGraphNode_IfIntegerVariable#FirstInteger is less, more or equal than UDialogGraphNode_IfIntegerVariable#SecondInteger.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Null if the variable identification is not valid, otherwise the next child to be executed.
	*/
	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(FirstInteger.Quest) || !IsValid(SecondInteger.Quest))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_IfIntegerVariable_GetNextNode", "DialogGraphNode_IfIntegerVariable:GetNextNode:Quest is null or invalid."));
			return nullptr;
		}
		int32 FirstVariableValue = FirstInteger.Quest->GetInteger(GameContext, FirstInteger.IntegerName);
		int32 SecondVariableValue = SecondInteger.Quest->GetInteger(GameContext, SecondInteger.IntegerName);
		if (FirstVariableValue < SecondVariableValue)
		{
			return ChildLess;
		}
		else if (FirstVariableValue == SecondVariableValue)
		{
			return ChildEqual;
		}
		else
		{
			return ChildMore;
		}
	}
};
