#include "QuestGraph.h"
#include "QuestGraphNode.h"
#include "QuestGraphNode_Flag.h"
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

void UQuestGraph::SetFlag(FName FlagName)
{
	for (auto* node : AllNodes)
	{
		auto* flagNode = Cast<UQuestGraphNode_Flag>(node);
		if (flagNode != nullptr && flagNode->FlagName == FlagName)
		{
			flagNode->FlagValue = true;
			break;
		}
	}
}

bool UQuestGraph::GetFlag(FName FlagName)
{
	for (auto* node : AllNodes)
	{
		auto* flagNode = Cast<UQuestGraphNode_Flag>(node);
		if (flagNode != nullptr && flagNode->FlagName == FlagName)
		{
			return flagNode->FlagValue;
		}
	}
	return false;
}

#undef LOCTEXT_NAMESPACE