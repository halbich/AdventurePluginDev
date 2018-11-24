#include "QuestGraph.h"
#include "QuestGraphNode.h"
#include "QuestGraphNode_Flag.h"
#include "Engine/Engine.h"
#include "AdventurePluginRuntime.h"
#include "AdventurePluginGameContext.h"

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

void UQuestGraph::SetFlag(UAdventurePluginGameContext* GameContext, FName FlagName)
{
	for (auto* node : AllNodes)
	{
		auto* flagNode = Cast<UQuestGraphNode_Flag>(node);
		if (flagNode != nullptr && flagNode->FlagName == FlagName)
		{
			if (!flagNode->ParentNodesSatisfied(GameContext))
			{
				auto flagNameText = FText::FromName(FlagName);
				LOG_Warning(FText::Format(NSLOCTEXT("AP", "Parent nodes not true", "Quest {0}: Quest flag set to true even though at least one of its predecessors are false. FlagName: {1}"), GetGraphNameText(), flagNameText));
			}
			flagNode->FlagValue = true;
			return;
		}
	}
	auto flagNameText = FText::FromName(FlagName);
	LOG_Error(FText::Format(NSLOCTEXT("AP", "Quest node not found", "Quest {0}: Cannot set a flag to true, flag with name {1} not found."), GetGraphNameText(), flagNameText));
}

bool UQuestGraph::GetFlag(UAdventurePluginGameContext* GameContext, FName FlagName)
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
FText UQuestGraph::GetGraphNameText()
{
	return FText::FromString(Name);
}

bool UQuestGraph::GetBool(FName VarName, bool bDefaultValue)
{
	auto* var = BoolVariables.Find(VarName);
	return var ? var->Value : bDefaultValue;
}

bool UQuestGraph::SetBool(FName VarName, bool bValue)
{
	auto* var = BoolVariables.Find(VarName);
	if (!var) return false;
	var->Value = bValue;
	return true;
}

int32 UQuestGraph::GetInteger(FName VarName, int32 DefaultValue)
{
	auto* var = IntegerVariables.Find(VarName);
	return var ? var->Value : DefaultValue;
}

bool UQuestGraph::SetInteger(FName VarName, int32 Value)
{
	auto* var = IntegerVariables.Find(VarName);
	if (!var) return false;
	var->Value = Value;
	return true;
}

FString UQuestGraph::GetString(FName VarName, FString DefaultValue)
{
	auto* var = StringVariables.Find(VarName);
	return var ? var->Value : DefaultValue;
}

bool UQuestGraph::SetString(FName VarName, FString Value)
{
	auto* var = StringVariables.Find(VarName);
	if (!var) return false;
	var->Value = Value;
	return true;
}

TArray<UQuestGraphNode*> UQuestGraph::GetSatisfiableNodes(UAdventurePluginGameContext* GameContext)
{
	auto toReturn = TArray<UQuestGraphNode*>();
	for (auto* childNode : AllNodes)
	{
		auto* childQuestNode = Cast<UQuestGraphNode>(childNode);
		if (childQuestNode == nullptr || !childQuestNode->IsValidLowLevel()) 
		{
			LOG_Error(FText::Format(NSLOCTEXT("AP", "Nil or invalid quest node", "Quest {0}: Nil node or node that is not a QuestGraphNode found in a quest graph"), GetGraphNameText()));
			continue;
		}
		if (!childQuestNode->IsSatisfied(GameContext) && childQuestNode->ParentNodesSatisfied(GameContext)) {
			toReturn.Add(childQuestNode);
		}
	}
	return toReturn;
}


#undef LOCTEXT_NAMESPACE