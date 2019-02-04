#include "Quest/EdQuestNode.h"
#include "Slate.h"
#include "Quest/SEdQuestNode.h"

TSharedPtr<class SGraphNode> UEdQuestNode::CreateVisualWidget()
{
	return SNew(SEdQuestNode, this);
}