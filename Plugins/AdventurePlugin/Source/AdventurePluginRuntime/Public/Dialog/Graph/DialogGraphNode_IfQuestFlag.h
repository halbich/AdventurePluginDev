#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphFlag.h"
#include "DialogGraphNode_IfQuestFlag.generated.h"

/**
* This node is a branch node that can return a different next node based
* on a value of a flag UDialogGraphNode_IfQuestFlag#Flag on a quest.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfQuestFlag : public UDialogGraphNode_TrueFalse
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfQuestFlag()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Branch on Quest Flag");
#endif
	}

	/**
	* Identifies the flag this node is working with.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnFlagNode")
	FQuestGraphFlag Flag;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfQuestFlag", "NodeTitle", "IF {0}->{1}"), 
			FText::FromString(IsValid(Flag.Quest) ? Flag.Quest->Name : "<EMPTY>"),
			FText::FromName(Flag.FlagName));
	}

#endif

	/**
	* This node is true if the flag UDialogGraphNode_IfQuestFlag#Flag is set.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return False if the flag specification is invalid or the flag is not set, otherwise true.
	*/
	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Flag.Quest))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_IfQuestFlag_IsTrue_QuestInvalid", "DialogGraphNode_IfQuestFlag:IsTrue:Quest is null or invalid."));
			return false;
		}
		return Flag.Quest->GetFlag(GameContext, Flag.FlagName);
	}
};
