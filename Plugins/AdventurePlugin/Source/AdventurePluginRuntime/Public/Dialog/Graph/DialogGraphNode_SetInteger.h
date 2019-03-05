#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphInteger.h"
#include "DialogGraphNode_SetInteger.generated.h"

/**
* This node sets a specific integer variable to the given value when executed.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SetInteger : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SetInteger()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_SetInteger_ContextName", "Set integer variable");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "ManipulationCategory", "Data Manipulation");
#endif
	}

	/**
	* Identifies the variable this node is working with.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetIntegerNode")
	FQuestGraphInteger Integer;

	/**
	* The constant to which set the variable.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetIntegerNode")
	int32 Constant;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_SetInteger", "NodeTitle", "Set {0}->{1} TO {2}"),
			FText::FromString(IsValid(Integer.Quest) ? Integer.Quest->Name : "<EMPTY>"),
			FText::FromName(Integer.IntegerName),
			Constant);
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor(0, 1, 1);
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

#endif

	/**
	* Sets the variable this node is pointing to to the given constant value.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Always true, this never halts the execution.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Integer.Quest))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_SetInteger_Execute_QuestInvalid", "DialogGraphNode_SetInteger:Execute:Quest is null or invalid."));
			return true;
		}
		Integer.Quest->SetInteger(GameContext, Integer.IntegerName, Constant);
		return true;
	};
};
