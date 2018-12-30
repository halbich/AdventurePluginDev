#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_EntryMain.h"
#include "DialogGraphNode_Event.h"
#include "Engine/Engine.h"

#define LOCTEXT_NAMESPACE "DialogGraph"

UDialogGraph::UDialogGraph()
	: UGenericGraph()
{
	NodeType = UDialogGraphNode::StaticClass();
	bEdgeEnabled = false;
}

UDialogGraph::~UDialogGraph()
{
}

UDialogGraphNode_Event* UDialogGraph::GetEventNode(FName EventName)
{
	for (auto* node : AllNodes)
	{
		UDialogGraphNode_Event* eventNode = Cast<UDialogGraphNode_Event>(node);
		if (eventNode != NULL && eventNode->IsValidLowLevel() && eventNode->Event.EventName == EventName)
		{
			return eventNode;
		}
	}
	return NULL;
}

#undef LOCTEXT_NAMESPACE