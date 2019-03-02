#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphInteger.h"
#include "DialogGraphNode_IncrementInteger.generated.h"

/**
* This node increments a specific variable when executed.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IncrementInteger : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IncrementInteger()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Increment integer variable");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "ManipulationCategory", "Data Manipulation");
#endif
	}

	/**
	* Identifies the variable this node is working with.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IncrementIntegerNode")
	FQuestGraphInteger Integer;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IncrementInteger", "NodeTitle", "INCREMENT {0}->{1}"),
			FText::FromString(IsValid(Integer.Quest) ? Integer.Quest->Name : "<EMPTY>"),
			FText::FromName(Integer.IntegerName));
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
	* Increments the variable this node is pointing to.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Always true, this never halts the execution.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Integer.Quest))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_IncrementInteger_Execute_QuestInvalid", "DialogGraphNode_IncrementInteger:Execute:Quest is null or invalid."));
			return true;
		}
		int32 OldValue = Integer.Quest->GetInteger(GameContext, Integer.IntegerName);
		Integer.Quest->SetInteger(GameContext, Integer.IntegerName, OldValue + 1);
		return true;
	};
};
