#include "QuestGraph.h"
#include "QuestGraphNode.h"
#include "Engine/Engine.h"

#define LOCTEXT_NAMESPACE "QuestGraph"

UQuestGraph::UQuestGraph()
	: UGenericGraph()
{
	NodeType = UQuestGraphNode::StaticClass();
	bEdgeEnabled = false;
}

UQuestGraph::~UQuestGraph()
{
}

#undef LOCTEXT_NAMESPACE