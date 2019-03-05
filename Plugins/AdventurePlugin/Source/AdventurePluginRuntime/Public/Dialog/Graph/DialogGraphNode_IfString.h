#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphString.h"
#include "DialogGraphNode_IfString.generated.h"

/**
* This node is a branch node that can return a different next node based
* on a value of a string variable UDialogGraphNode_IfString#String on a quest.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfString : public UDialogGraphNode_TrueFalse
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfString()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_IfString_ContextName", "Branch on string variable equality with a constant");
#endif
	}

	/**
	* Identifies the variable this node is working with.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnStringNode")
	FQuestGraphString String;

	/**
	* The constant with which we are comparing the string.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnStringNode")
	FString Constant;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfString", "NodeTitle", "IF {0}->{1} IS {2}"), 
			FText::FromString(IsValid(String.Quest) ? String.Quest->Name : "<EMPTY>"),
			FText::FromName(String.StringName), 
			FText::FromString(Constant));
	}

#endif

	/**
	* This node is true if the string UDialogGraphNode_IfString#String is the same
	* as the constant UDialogGraphNode_IfString#Constant.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return False if the variable specification is invalid or the string is not the same as the constant, otherwise true.
	*/
	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(String.Quest))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_IfString_IsTrue_QuestInvalid", "DialogGraphNode_IfString:IsTrue:Quest is null or invalid."));
			return false;
		}
		return Constant.Compare(String.Quest->GetString(GameContext, String.StringName)) == 0;
	}
};
