#pragma once

#include "CoreMinimal.h"
#include "QuestGraphNode.h"
#include "AdventurePluginRuntime.h"
#include "QuestGraphNode_Flag.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UQuestGraphNode_Flag : public UQuestGraphNode
{
	GENERATED_BODY()

public:

	UQuestGraphNode_Flag()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("QuestGraphNode_Flag", "ContextMenuName", "Simple flag");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlagNode")
	FName FlagName;

	virtual bool IsSatisfied(UAdventurePluginGameContext* GameContext) override
	{
		UQuestGraph* ParentGraph = Cast<UQuestGraph>(Graph);
		if (!IsValid(ParentGraph))
		{
			LOG_Warning(NSLOCTEXT("AP", "QuestGraphNode_Flag", "QuestGraphNode_Flag:IsSatisfied:Graph is invalid."));
			return false;
		}
		return ParentGraph->GetFlag(GameContext, FlagName);
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const override
	{
		return FText::FromName(FlagName);
	}

	virtual void SetNodeTitle(const FText & NewTitle) override
	{
		FlagName = FName(*NewTitle.ToString());
	}

	virtual inline FLinearColor GetBackgroundColor() const override
	{
		return FLinearColor::Yellow;
	}

	virtual inline bool CanRename() const override
	{
		return true;
	}

#endif
};
