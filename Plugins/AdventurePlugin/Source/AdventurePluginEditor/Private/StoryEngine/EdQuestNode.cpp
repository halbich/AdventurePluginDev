#include "StoryEngine/EdQuestNode.h"
#include "Slate.h"
#include "StoryEngine/SEdQuestNode.h"

TSharedPtr<class SGraphNode> UEdQuestNode::CreateVisualWidget()
{
	return SNew(SEdQuestNode, this);
}