#include "EdQuestNode.h"
#include "Slate.h"
#include "SEdQuestNode.h"

TSharedPtr<class SGraphNode> UEdQuestNode::CreateVisualWidget()
{
	return SNew(SEdQuestNode, this);
}