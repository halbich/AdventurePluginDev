#include "QuestGraph.h"
#include "QuestGraphNode.h"
#include "QuestGraphNode_Flag.h"
#include "Engine/Engine.h"
#include "AdventurePluginRuntime.h"
#include "SaveGame/AdventurePluginSaveGame.h"
#include "AdventurePluginGameContext.h"

#define LOCTEXT_NAMESPACE "QuestGraph"

UQuestGraph::UQuestGraph()
	: UGenericGraph()
{
	NodeType = UQuestGraphNode::StaticClass();
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

bool UQuestGraph::GetBool(UAdventurePluginGameContext* GameContext, FName VarName)
{
	bool bDefaultValue(false);
	if (!GameContext || !GameContext->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "QuestGraph::GetBool::gameContext is NULL"));
		return bDefaultValue;
	}

	auto save = GameContext->SaveGame;
	if (!save || !save->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextSaveGameNull", "QuestGraph::GetBool::gameContext::SaveGame is NULL"));
		return bDefaultValue;
	}

	FBoolVariable* var = BoolVariables.Find(VarName);
	if (!var)
	{
		LOG_Error(NSLOCTEXT("AP", "VariableNotFound", "QuestGraph::GetBool - Variable was not found in dictionary"));
		return bDefaultValue;
	}

	return save->GetBoolOrDefault(VarName, var->DefaultValue);
}

bool UQuestGraph::SetBool(UAdventurePluginGameContext* GameContext, FName VarName, bool bValue)
{
	if (!GameContext || !GameContext->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "QuestGraph::SetBool::gameContext is NULL"));
		return false;
	}
	auto save = GameContext->SaveGame;
	if (!save || !save->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextSaveGameNull", "QuestGraph::SetBool::gameContext::SaveGame is NULL"));
		return false;
	}

	if (!BoolVariables.Find(VarName))
	{
		LOG_Error(NSLOCTEXT("AP", "VariableNotFound", "QuestGraph::SetBool - Variable was not found in dictionary"));
		return false;
	}

	save->SetBool(VarName, bValue);
	return true;
}

int32 UQuestGraph::GetInteger(UAdventurePluginGameContext* GameContext, FName VarName)
{
	int32 DefaultValue(0);
	if (!GameContext || !GameContext->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "QuestGraph::GetInteger::gameContext is NULL"));
		return DefaultValue;
	}
	auto save = GameContext->SaveGame;
	if (!save || !save->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextSaveGameNull", "QuestGraph::GetInteger::gameContext::SaveGame is NULL"));
		return DefaultValue;
	}

	FIntegerVariable* var = IntegerVariables.Find(VarName);
	if (!var)
	{
		LOG_Error(NSLOCTEXT("AP", "VariableNotFound", "QuestGraph::GetInteger - Variable was not found in dictionary"));
		return DefaultValue;
	}

	return save->GetIntOrDefault(VarName, var->DefaultValue);
}

bool UQuestGraph::SetInteger(UAdventurePluginGameContext* GameContext, FName VarName, int32 Value)
{
	if (!GameContext || !GameContext->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "QuestGraph::SetInteger::gameContext is NULL"));
		return false;
	}
	auto save = GameContext->SaveGame;
	if (!save || !save->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextSaveGameNull", "QuestGraph::SetInteger::gameContext::SaveGame is NULL"));
		return false;
	}

	if (!IntegerVariables.Find(VarName))
	{
		LOG_Error(NSLOCTEXT("AP", "VariableNotFound", "QuestGraph::SetInteger - Variable was not found in dictionary"));
		return false;
	}

	save->SetInt(VarName, Value);
	return true;
}

FString UQuestGraph::GetString(UAdventurePluginGameContext* GameContext, FName VarName)
{
	FString DefaultValue;

	if (!GameContext || !GameContext->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "QuestGraph::GetString::gameContext is NULL"));
		return DefaultValue;
	}
	auto save = GameContext->SaveGame;
	if (!save || !save->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextSaveGameNull", "QuestGraph::GetString::gameContext::SaveGame is NULL"));
		return DefaultValue;
	}

	FStringVariable* var = StringVariables.Find(VarName);
	if (!var)
	{
		LOG_Error(NSLOCTEXT("AP", "VariableNotFound", "QuestGraph::GetString - Variable was not found in dictionary"));
		return DefaultValue;
	}

	return save->GetStringOrDefault(VarName, var->DefaultValue);
}

bool UQuestGraph::SetString(UAdventurePluginGameContext* GameContext, FName VarName, FString Value)
{
	if (!GameContext || !GameContext->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextNull", "QuestGraph::SetString::gameContext is NULL"));
		return false;
	}
	auto save = GameContext->SaveGame;
	if (!save || !save->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextSaveGameNull", "QuestGraph::SetString::gameContext::SaveGame is NULL"));
		return false;
	}

	if (!StringVariables.Find(VarName))
	{
		LOG_Error(NSLOCTEXT("AP", "VariableNotFound", "QuestGraph::SetString - Variable was not found in dictionary"));
		return false;
	}

	save->SetString(VarName, Value);
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