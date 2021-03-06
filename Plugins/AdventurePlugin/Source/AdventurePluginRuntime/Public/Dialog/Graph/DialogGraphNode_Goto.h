#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraph.h"
#include "AdventurePluginRuntime.h"
#include "DialogGraphNode_Goto.generated.h"

/**
* This node serves to easily navigate to some other node in the graph by UDialogGraphNode#Id.
* The node does nothing by itself, but the next node to be executed is specified by
* UDialogGraphNode_Goto#TargetNodeId instead of edge.
* Use to make the graph more readable, for example to navigate back to the option selection.
* The other use case is to create cycles, as the graph does not support cycles by itself.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Goto : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Goto()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_Goto_ContextName", "Goto");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "OtherCategory", "Other");
#endif
	}

	virtual ~UDialogGraphNode_Goto()
	{
	}

	/**
	* Defines the next node to be executed.
	*/
	UPROPERTY(EditAnywhere, Category = "GotoNode")
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

	/**
	* Returns the next node to be executed, which is specified by the UDialogGraphNode_Goto#TargetNodeId.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The next node to be executed, or null if the target node id does not point to a valid node.
	*/
	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* GameContext) override
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		if (!IsValid(DialogGraph))
		{
			LOG_Warning(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_Goto_GetNextNode_GraphInvalid", "DialogGraphNode_Goto:GetNextNode:Graph is null or invalid."));
			return nullptr;
		}
		UDialogGraphNode** TargetNode = DialogGraph->IdToNodeMap.Find(TargetNodeId);
		if (TargetNode == nullptr || !IsValid(*TargetNode))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_Goto_GetNextNode_InvalidTarget", "DialogGraphNode_Goto:GetNextNode: Invalid target Id"));
			return nullptr;
		}
		return *TargetNode;
	}
};
