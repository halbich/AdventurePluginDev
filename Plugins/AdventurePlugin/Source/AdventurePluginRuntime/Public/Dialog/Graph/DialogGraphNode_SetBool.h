#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphBool.h"
#include "DialogGraphNode_SetBool.generated.h"
/**
* This node sets a specific bool variable to the opposite value than what it currently has..
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SetBool : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SetBool()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Set value of bool variable");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "ManipulationCategory", "Data Manipulation");
#endif
	}
	/**
	* Identifies the variable to be modified.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetBoolNode")
		FQuestGraphBool Bool;
	/**
	* The constant to which set the variable.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetBoolNode")
		bool bConstant;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_SetBool", "NodeTitle", "Set {0}->{1} TO {2}"),
			FText::FromString(IsValid(Bool.Quest) ? Bool.Quest->Name : "<EMPTY>"),
			FText::FromName(Bool.BoolName),
			bConstant ? NSLOCTEXT("AP", "TrueConstant", "true") : NSLOCTEXT("AP","FalseConstant", "false"));
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
	/* Sets the bool variable on the quest to a specified constant value.
	* @see UDialogGraphNode_SetBool#Bool
	* @see UDialogGraphNode_SetBool#bConstant
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Always true. This should never halt execution.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Bool.Quest))
		{
			LOG_Warning(NSLOCTEXT("AP", "DialogGraphNode_SetBoolQuestInvalid", "DialogGraphNode_SetBool:Execute: Quest null or invalid."));
			return true;
		}
		Bool.Quest->SetBool(GameContext, Bool.BoolName, bConstant);
		return true;
	};
};
