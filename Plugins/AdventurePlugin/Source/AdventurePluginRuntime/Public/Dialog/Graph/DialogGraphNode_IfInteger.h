#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphInteger.h"
#include "DialogGraphNode_IfInteger.generated.h"
/**
* This node is a branch node that can return a different next node based on a value of an integer variable on a quest.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfInteger : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfInteger()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Branch on integer variable");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "BranchingCategory", "Branching");
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
	/**
	* The child with which we should continue if the represented variable is less than the constant.
	* #see UDialogGraphNode_IfInteger#Integer
	* #see UDialogGraphNode_IfInteger#Constant
	*/
	UPROPERTY(BlueprintReadOnly)
	UDialogGraphNode* ChildLess;
	/**
	* The child with which we should continue if the represented variable is equal to the constant.
	* #see UDialogGraphNode_IfInteger#Integer
	* #see UDialogGraphNode_IfInteger#Constant
	*/
	UPROPERTY(BlueprintReadOnly)
	UDialogGraphNode* ChildEqual;
	/**
	* The child with which we should continue if the represented variable is more than the constant.
	* #see UDialogGraphNode_IfInteger#Integer
	* #see UDialogGraphNode_IfInteger#Constant
	*/
	UPROPERTY(BlueprintReadOnly)
	UDialogGraphNode* ChildMore;

	virtual void ResetSpecialChildren() override
	{
		ChildLess = nullptr;
		ChildEqual = nullptr;
		ChildMore = nullptr;
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfInteger", "NodeTitle", "COMPARE {0}->{1} WITH {2}"),
			FText::FromString(IsValid(Integer.Quest) ? Integer.Quest->Name : "<EMPTY>"),
			FText::FromName(Integer.IntegerName),
			Constant);
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::White;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

#endif
	/**
	* Returns the next node to be executed, based on the value of the relevant int variable and constant, whether the variable is less, more or equal than the constant.
	* #see UDialogGraphNode_IfInteger#Integer
	* #see UDialogGraphNode_IfInteger#Constant
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Null if the variable identification is not valid, otherwise the next child to be executed.
	*/
	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Integer.Quest))
		{
			LOG_Warning(NSLOCTEXT("AP", "DialogGraphNode_IfInteger", "DialogGraphNode_IfInteger:GetNextNode:Quest is null or invalid."));
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
