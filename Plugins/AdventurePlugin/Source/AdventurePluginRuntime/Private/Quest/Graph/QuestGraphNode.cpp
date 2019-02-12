#include "QuestGraphNode.h"
#include "QuestGraph.h"

#define LOCTEXT_NAMESPACE "QuestGraphNode"

UQuestGraphNode::UQuestGraphNode()
{
#if WITH_EDITORONLY_DATA

	CompatibleGraphType = UQuestGraph::StaticClass();
	ContextMenuCategory = NSLOCTEXT("NodeCategories", "QuestNodeCategory", "Quest Nodes");

#endif
}

UQuestGraphNode::~UQuestGraphNode()
{
}


bool UQuestGraphNode::ParentNodesSatisfied(UAdventurePluginGameContext* GameContext) {
	for (UGenericGraphNode* ParentNodeUncasted : ParentNodes) {
		UQuestGraphNode* ParentNode = Cast<UQuestGraphNode>(ParentNodeUncasted);
		if (ParentNode == nullptr || !ParentNode->IsValidLowLevel())
		{
			continue;
		}
		if (!ParentNode->IsSatisfied(GameContext)) {
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