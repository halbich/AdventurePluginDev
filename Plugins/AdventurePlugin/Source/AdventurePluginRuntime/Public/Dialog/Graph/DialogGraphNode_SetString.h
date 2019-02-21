#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphString.h"
#include "DialogGraphNode_SetString.generated.h"
/**
* This node sets a specific string variable on a quest to a constant value.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SetString : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SetString()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Set string variable");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "ManipulationCategory", "Data Manipulation");
#endif
	}
	/**
	* Identifies the variable to be modified.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetStringNode")
	FQuestGraphString String;
	/**
	* To what should we set the variable this node points to.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetStringNode")
	FString Constant;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_SetString", "NodeTitle", "SET {0}->{1} TO {2}"),
			FText::FromString(IsValid(String.Quest) ? String.Quest->Name : "<EMPTY>"),
			FText::FromName(String.StringName), 
			FText::FromString(Constant));
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
	/* Sets the string variable on the quest to a specific constant value if the quest identification is valid.
	* @see UDialogGraphNode_SetString#String
	* @see UDialogGraphNode_SetString#Constant
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Always true. This should never halt execution.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(String.Quest))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_SetString_Execute_QuestInvalid", "DialogGraphNode_SetString:Execute:Quest is null or invalid."));
			return true;
		}
		String.Quest->SetString(GameContext, String.StringName, Constant);
		return true;
	};
};
