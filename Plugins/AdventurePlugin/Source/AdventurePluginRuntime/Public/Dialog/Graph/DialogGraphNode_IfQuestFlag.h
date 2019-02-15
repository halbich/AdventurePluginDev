#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphFlag.h"
#include "DialogGraphNode_IfQuestFlag.generated.h"

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
	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Flag.Quest))
		{
			LOG_Warning(NSLOCTEXT("AP", "DialogGraphNode_IfQuestFlagQuestInvalid", "DialogGraphNode_IfQuestFlag:IsTrue:Quest is null or invalid."));
			return false;
		}
		return Flag.Quest->GetFlag(GameContext, Flag.FlagName);
	}
};
