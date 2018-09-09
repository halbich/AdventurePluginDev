#include "QuestGraphNode.h"
#include "QuestGraph.h"

#define LOCTEXT_NAMESPACE "QuestGraphNode"

UQuestGraphNode::UQuestGraphNode()
{
#if WITH_EDITORONLY_DATA

	CompatibleGraphType = UQuestGraph::StaticClass();

#endif
}

UQuestGraphNode::~UQuestGraphNode()
{
}

#if WITH_EDITOR

bool UQuestGraphNode::CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
{
	return true;
}

#endif

#undef LOCTEXT_NAMESPACE