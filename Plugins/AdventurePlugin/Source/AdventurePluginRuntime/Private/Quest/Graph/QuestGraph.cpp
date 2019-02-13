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
	//TODO: This checking is for every method here, could be refactored outside.
	if (!IsValid(GameContext) || !IsValid(GameContext->SaveGame))
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextInvalid", "QuestGraph::GetFlag::gameContext is invalid"));
		return;
	}
	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;
	FText FlagNameText = FText::FromName(FlagName);
	for (UGenericGraphNode* Node : AllNodes)
	{
		UQuestGraphNode_Flag* FlagNode = Cast<UQuestGraphNode_Flag>(Node);
		if (FlagNode != nullptr && FlagNode->FlagName == FlagName)
		{
			if (!FlagNode->ParentNodesSatisfied(GameContext))
			{
				LOG_Warning(FText::Format(NSLOCTEXT("AP", "Parent nodes not true", "Quest {0}: Quest flag set to true even though at least one of its predecessors are false. FlagName: {1}"), GetGraphNameText(), FlagNameText));
			}
			//TODO: Actually differentiate between flags and bools.
			SaveGame->SetBool(FlagName, true);
			return;
		}
	}
	LOG_Error(FText::Format(NSLOCTEXT("AP", "Quest node not found", "Quest {0}: Cannot set a flag to true, flag with name {1} not found."), GetGraphNameText(), FlagNameText));
}
 
bool UQuestGraph::GetFlag(UAdventurePluginGameContext* GameContext, FName FlagName)
{
	if (!IsValid(GameContext) || !IsValid(GameContext->SaveGame))
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextInvalid", "QuestGraph::GetFlag::gameContext is invalid."));
		return false;
	}
	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;
	for (UGenericGraphNode* Node : AllNodes)
	{
		UQuestGraphNode_Flag* FlagNode = Cast<UQuestGraphNode_Flag>(Node);
		if (FlagNode != nullptr && FlagNode->FlagName == FlagName)
		{
			return SaveGame->GetBoolOrDefault(FlagName, false);
		}
	}
	//TODO: Warning
	return false;
}
FText UQuestGraph::GetGraphNameText()
{
	return FText::FromString(Name);
}

bool UQuestGraph::GetBool(UAdventurePluginGameContext* GameContext, FName VariableName)
{
	bool bDefaultValue(false);
	if (!IsValid(GameContext) || !IsValid(GameContext->SaveGame))
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextInvalid", "QuestGraph::GetBool::gameContext is invalid"));
		return bDefaultValue;
	}

	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;

	FBoolVariable* BoolVariable = BoolVariables.Find(VariableName);
	if (!BoolVariable)
	{
		LOG_Error(NSLOCTEXT("AP", "VariableNotFound", "QuestGraph::GetBool - Variable was not found in dictionary"));
		return bDefaultValue;
	}

	return SaveGame->GetBoolOrDefault(VariableName, BoolVariable->DefaultValue);
}

bool UQuestGraph::SetBool(UAdventurePluginGameContext* GameContext, FName VariableName, bool bValue)
{
	if (!IsValid(GameContext) || !IsValid(GameContext->SaveGame))
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextInvalid", "QuestGraph::SetBool::gameContext is invalid."));
		return false;
	}
	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;

	if (!BoolVariables.Find(VariableName))
	{
		LOG_Error(NSLOCTEXT("AP", "VariableNotFound", "QuestGraph::SetBool - Variable was not found in dictionary"));
		return false;
	}

	SaveGame->SetBool(VariableName, bValue);
	return true;
}

int32 UQuestGraph::GetInteger(UAdventurePluginGameContext* GameContext, FName VariableName)
{
	int32 DefaultValue(0);
	if (!IsValid(GameContext) || !IsValid(GameContext->SaveGame))
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextInvalid", "QuestGraph::GetInteger::gameContext is invalid."));
		return DefaultValue;
	}
	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;

	FIntegerVariable* IntegerVariable = IntegerVariables.Find(VariableName);
	if (!IntegerVariable)
	{
		LOG_Error(NSLOCTEXT("AP", "VariableNotFound", "QuestGraph::GetInteger - Variable was not found in dictionary"));
		return DefaultValue;
	}

	return SaveGame->GetIntOrDefault(VariableName, IntegerVariable->DefaultValue);
}

bool UQuestGraph::SetInteger(UAdventurePluginGameContext* GameContext, FName VariableName, int32 Value)
{
	if (!IsValid(GameContext) || !IsValid(GameContext->SaveGame))
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextInvalid.", "QuestGraph::SetInteger::gameContext is invalid."));
		return false;
	}
	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;

	if (!IntegerVariables.Find(VariableName))
	{
		LOG_Error(NSLOCTEXT("AP", "VariableNotFound", "QuestGraph::SetInteger - Variable was not found in dictionary"));
		return false;
	}

	SaveGame->SetInt(VariableName, Value);
	return true;
}

FString UQuestGraph::GetString(UAdventurePluginGameContext* GameContext, FName VariableName)
{
	FString DefaultValue;

	if (!IsValid(GameContext) || !IsValid(GameContext->SaveGame))
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextInvalid", "QuestGraph::GetString::gameContext is invalid."));
		return DefaultValue;
	}
	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;

	FStringVariable* StringVariable = StringVariables.Find(VariableName);
	if (!StringVariable)
	{
		LOG_Error(NSLOCTEXT("AP", "VariableNotFound", "QuestGraph::GetString - Variable was not found in dictionary"));
		return DefaultValue;
	}

	return SaveGame->GetStringOrDefault(VariableName, StringVariable->DefaultValue);
}

bool UQuestGraph::SetString(UAdventurePluginGameContext* GameContext, FName VariableName, FString Value)
{
	if (!IsValid(GameContext) || !IsValid(GameContext->SaveGame))
	{
		LOG_Error(NSLOCTEXT("AP", "GameContextInvalid", "QuestGraph::SetString::gameContext is invalid."));
		return false;
	}
	UAdventurePluginSaveGame* SaveGame = GameContext->SaveGame;

	if (!StringVariables.Find(VariableName))
	{
		LOG_Error(NSLOCTEXT("AP", "VariableNotFound", "QuestGraph::SetString - Variable was not found in dictionary"));
		return false;
	}

	SaveGame->SetString(VariableName, Value);
	return true;
}

TArray<UQuestGraphNode*> UQuestGraph::GetSatisfiableNodes(UAdventurePluginGameContext* GameContext)
{
	TArray<UQuestGraphNode*> SatisfiableNodes = TArray<UQuestGraphNode*>();
	for (UGenericGraphNode* ChildNode : AllNodes)
	{
		UQuestGraphNode* ChildQuestNode = Cast<UQuestGraphNode>(ChildNode);
		if (!IsValid(ChildQuestNode))
		{
			LOG_Error(FText::Format(NSLOCTEXT("AP", "Nil or invalid quest node", "Quest {0}: Nil node or node that is not a QuestGraphNode found in a quest graph"), GetGraphNameText()));
			continue;
		}
		if (!ChildQuestNode->IsSatisfied(GameContext) && ChildQuestNode->ParentNodesSatisfied(GameContext)) {
			SatisfiableNodes.Add(ChildQuestNode);
		}
	}
	return SatisfiableNodes;
}

#undef LOCTEXT_NAMESPACE