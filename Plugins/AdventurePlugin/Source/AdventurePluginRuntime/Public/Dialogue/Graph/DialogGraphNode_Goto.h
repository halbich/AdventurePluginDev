#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraph.h"
#include "AdventurePluginRuntime.h"
#include "DialogGraphNode_Goto.generated.h"

#pragma optimize("", off)
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Goto : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Goto()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Goto");
#endif
	}

	virtual ~UDialogGraphNode_Goto()
	{
	}

	UPROPERTY(EditAnywhere, Category = "DialogGraphNode_Editor")
		FName TargetNodeId;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		if (TargetNodeId.IsNone()) 
		{
			return NSLOCTEXT("DialogGraphNode_Goto", "Goto no target title", "Goto: No target set");
		}
		else 
		{
			return FText::Format(NSLOCTEXT("DialogGraphNode_Goto", "Goto title", "Goto: {0}"), FText::FromName(TargetNodeId));
		}
	}

	virtual void SetNodeTitle(const FText& NewTitle) override
	{
		TargetNodeId = FName(*NewTitle.ToString());
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::White;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

	virtual uint32 GetOutputPinsCount() const override
	{
		return 0;
	}

	virtual UDialogGraphNode* GetNextNode() override
	{
		auto* dialogueGraph = Cast<UDialogGraph>(Graph);
		if (dialogueGraph == NULL || !dialogueGraph->IsValidLowLevel()) 
		{
			LOG_Error(NSLOCTEXT("AP", "InvalidDialogGraph", "GotoNode: Parent graph is not a dialog graph"));
			return NULL;
		}
		auto* targetNode = dialogueGraph->IdToNodeMap.Find(TargetNodeId);
		if (targetNode == NULL || *targetNode == NULL || !(*targetNode)->IsValidLowLevel())
		{
			LOG_Error(NSLOCTEXT("AP", "InvalidDialogGraph", "GotoNode: Invalid target Id"));
			return NULL;
		}
		return *targetNode;
	}

#endif
};

#pragma optimize("", on)