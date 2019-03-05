#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphBool.h"
#include "DialogGraphNode_IfBoolVariable.generated.h"

/**
* This node is a branch node that can return a different next node based on equality between the values
* of quest bool variables. @see UDialogGraphNode_IfBoolVariable#FirstBool, @see UDialogGraphNode_IfBoolVariable#SecondBool.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfBoolVariable : public UDialogGraphNode_TrueFalse
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfBoolVariable()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_IfBoolVariable_ContextName", "Branch on bool variable equality with a variable");
#endif
	}

	/**
	* Identifies the first variable in the comparison.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnBoolNodeWithVariable")
	FQuestGraphBool FirstBool;

	/**
	* Identifies the second variable in the comparison.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnBoolNodeWithVariable")
	FQuestGraphBool SecondBool;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfBoolVariable", "NodeTitle", "IF {0}->{1} EQUALS {2}->{3}"),
			FText::FromString(IsValid(FirstBool.Quest) ? FirstBool.Quest->Name : "<EMPTY>"),
			FText::FromName(FirstBool.BoolName),
			FText::FromString(IsValid(SecondBool.Quest) ? SecondBool.Quest->Name : "<EMPTY>"),
			FText::FromName(SecondBool.BoolName));
	}

#endif

	/**
	* This node is true if the variable UDialogGraphNode_IfBoolVariable#FirstBool is equal to UDialogGraphNode_IfBoolVariable#SecondBool.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return False if the variable specification is invalid, otherwise value of that variable.
	*/
	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(FirstBool.Quest) || !IsValid(SecondBool.Quest))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_IfBoolVariable_IsTrue", "DialogGraphNode_IfBoolVariable:IsTrue:Quest is null or invalid."));
			return false;
		}
		return FirstBool.Quest->GetBool(GameContext, FirstBool.BoolName) == SecondBool.Quest->GetBool(GameContext, SecondBool.BoolName);
	}
};
