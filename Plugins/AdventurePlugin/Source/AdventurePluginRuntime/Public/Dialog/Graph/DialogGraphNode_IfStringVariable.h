#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphString.h"
#include "DialogGraphNode_IfStringVariable.generated.h"

/**
* This node is a branch node that can return a different next node based
* on equality between the values of two string variables, @see UDialogGraphNode_IfStringVariable#String.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfStringVariable : public UDialogGraphNode_TrueFalse
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfStringVariable()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Branch on string variable equality with a variable");
#endif
	}

	/**
	* Identifies the first variable in the comparison.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnStringNode")
	FQuestGraphString FirstString;

	/**
	* Identifies the second variable in the comparison.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnStringNode")
	FQuestGraphString SecondString;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfStringVariable", "NodeTitle", "IF {0}->{1} IS {2}->{3}"), 
			FText::FromString(IsValid(FirstString.Quest) ? FirstString.Quest->Name : "<EMPTY>"),
			FText::FromName(FirstString.StringName),
			FText::FromString(IsValid(SecondString.Quest) ? SecondString.Quest->Name : "<EMPTY>"),
			FText::FromName(SecondString.StringName));
	}

#endif

	/**
	* This node is true if the string UDialogGraphNode_IfStringVariable#FirstString is the same
	* as the variable UDialogGraphNode_IfStringVariable#SecondString.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return False if the variable specification is invalid or the string is not the same as the variable, otherwise true.
	*/
	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(FirstString.Quest) || !IsValid(SecondString.Quest))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_IfStringVariable_IsTrue_QuestInvalid", "DialogGraphNode_IfStringVariable:IsTrue:Quest is null or invalid."));
			return false;
		}
		return FirstString.Quest->GetString(GameContext, FirstString.StringName).Compare(SecondString.Quest->GetString(GameContext, SecondString.StringName)) == 0;
	}
};
