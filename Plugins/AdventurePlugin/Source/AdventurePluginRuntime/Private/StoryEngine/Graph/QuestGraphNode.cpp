#include "QuestGraphNode.h"
#include "QuestGraph.h"

#define LOCTEXT_NAMESPACE "QuestGraphNode"

UQuestGraphNode::UQuestGraphNode()
{
#if WITH_EDITORONLY_DATA
	CompatibleGraphType = UQuestGraph::StaticClass();
	//BackgroundColor = FLinearColor::Red;
#endif
}

UQuestGraphNode::~UQuestGraphNode()
{
}

FText UQuestGraphNode::GetDescription_Implementation() const
{
	return LOCTEXT("NodeDesc", "Quest Graph Node");
}

#if WITH_EDITOR

void UQuestGraphNode::SetNodeTitle(const FText & NewTitle)
{
	//DialogText = NewTitle;
}

bool UQuestGraphNode::CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
{
	return true;
}

#endif

#undef LOCTEXT_NAMESPACE