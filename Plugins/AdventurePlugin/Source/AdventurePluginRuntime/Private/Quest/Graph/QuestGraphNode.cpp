#include "Quest/Graph/QuestGraphNode.h"
#include "Quest/Graph/QuestGraph.h"

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

bool UQuestGraphNode::ParentNodesTrue(UAdventurePluginGameContext* GameContext, UObject* WorldObjectContext) {
	for (UGenericGraphNode* ParentNodeUncasted : ParentNodes) {
		UQuestGraphNode* ParentNode = Cast<UQuestGraphNode>(ParentNodeUncasted);
		if (!IsValid(ParentNode))
		{
			continue;
		}
		if (!ParentNode->IsTrue(GameContext, WorldObjectContext)) {
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