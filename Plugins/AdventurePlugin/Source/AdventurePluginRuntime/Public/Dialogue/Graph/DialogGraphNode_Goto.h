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
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "OtherCategory", "Other");
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
			return NSLOCTEXT("DialogGraphNode_Goto", "Goto no target title", "GOTO: No target set");
		}
		else 
		{
			return FText::Format(NSLOCTEXT("DialogGraphNode_Goto", "Goto title", "GOTO: {0}"), FText::FromName(TargetNodeId));
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

#endif

	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* context) override
	{
		auto* dialogueGraph = Cast<UDialogGraph>(Graph);
		if (dialogueGraph == nullptr || !dialogueGraph->IsValidLowLevel())
		{
			LOG_Error(NSLOCTEXT("AP", "InvalidDialogGraph", "GotoNode: Parent graph is not a dialog graph"));
			return nullptr;
		}
		auto* targetNode = dialogueGraph->IdToNodeMap.Find(TargetNodeId);
		if (targetNode == nullptr || *targetNode == nullptr || !(*targetNode)->IsValidLowLevel())
		{
			LOG_Error(NSLOCTEXT("AP", "InvalidDialogGraph", "GotoNode: Invalid target Id"));
			return nullptr;
		}
		return *targetNode;
	}
};

#pragma optimize("", on)