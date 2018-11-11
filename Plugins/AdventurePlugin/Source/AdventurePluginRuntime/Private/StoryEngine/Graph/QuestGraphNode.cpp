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


bool UQuestGraphNode::ParentNodesSatisfied(UAdventurePluginGameContext* GameContext) {
	for (auto* parentNodeUncasted : ParentNodes) {
		auto* parentNode = Cast<UQuestGraphNode>(parentNodeUncasted);
		if (parentNode == NULL || !parentNode->IsValidLowLevel())
		{
			continue;
		}
		if (!parentNode->IsSatisfied(GameContext)) {
			return false;
		}
	}
	return true;
}

#if WITH_EDITOR

bool UQuestGraphNode::CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
{
	return true;
}

bool UQuestGraphNode::CanRename() const
{
	return false;
}

#endif

#undef LOCTEXT_NAMESPACE