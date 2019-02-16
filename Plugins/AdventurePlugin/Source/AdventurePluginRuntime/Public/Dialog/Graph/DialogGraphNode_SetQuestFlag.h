#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphFlag.h"
#include "DialogGraphNode_SetQuestFlag.generated.h"
/**
* This node sets a specific flag on a quest.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SetQuestFlag : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SetQuestFlag()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Set Quest Flag");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "ManipulationCategory", "Data Manipulation");
#endif
	}
	/**
	* Identifies the flag to be set.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetFlagNode")
	FQuestGraphFlag Flag;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_SetQuestFlag", "NodeTitle", "SET {0}->{1}"), 
			FText::FromString(IsValid(Flag.Quest) ? Flag.Quest->Name : "<EMPTY>"),
			FText::FromName(Flag.FlagName));
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
	/* Sets the flag on the quest if the quest identification is valid.
	* @see UDialogGraphNode_SetQuestFlag#Flag
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Always true. This should never halt execution.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Flag.Quest))
		{
			LOG_Warning(NSLOCTEXT("AP", "DialogGraphNode_SetQuestFlagQuestInvalid", "DialogGraphNode_SetQuestFlag:Execute:Quest is null or invalid."));
			return true;
		}
		Flag.Quest->SetFlag(GameContext, Flag.FlagName);
		return true;
	};
};
