#pragma once

#include "CoreMinimal.h"
#include "QuestGraphNode.h"
#include "AdventurePluginRuntime.h"
#include "Common/AdventurePluginGameContext.h"
#include "QuestGraph.h"
#include "QuestGraphNode_Flag.generated.h"

/**
* Represents a simple flag that can be set to true by any outside code.
* Once true it can never be false again.
*/
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

	/**
	* The human readable name identifying this flag.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FlagNode")
	FName FlagName;

	virtual bool IsTrue(UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext) override
	{
		auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
		UQuestGraph* ParentGraph = Cast<UQuestGraph>(Graph);
		if (!IsValid(ParentGraph))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestGraphNode_Flag_IsTrue_GraphInvalid", "QuestGraphNode_Flag:IsTrue:Graph is invalid."));
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
