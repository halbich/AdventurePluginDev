#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_EntryMain.h"
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

#undef LOCTEXT_NAMESPACE