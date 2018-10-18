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


#undef LOCTEXT_NAMESPACE