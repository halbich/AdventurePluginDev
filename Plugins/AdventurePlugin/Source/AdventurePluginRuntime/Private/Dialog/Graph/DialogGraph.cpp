#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_EntryMain.h"
#include "DialogGraphNode_Event.h"
#include "AdventurePluginGameContext.h"
#include "AdventureCharacterManager.h"
#include "Engine/Engine.h"

#define LOCTEXT_NAMESPACE "DialogGraph"

const FName UDialogGraph::MainEntryName = FName("MAIN");

UDialogGraph::UDialogGraph()
	: UGenericGraph()
{
	NodeType = UDialogGraphNode::StaticClass();
}

UDialogGraph::~UDialogGraph()
{
}

UDialogGraphNode_Event* UDialogGraph::GetEventNode(FName EventName)
{
	for (auto* node : AllNodes)
	{
		UDialogGraphNode_Event* eventNode = Cast<UDialogGraphNode_Event>(node);
		if (eventNode != NULL && eventNode->IsValidLowLevel() && eventNode->Event.EventName == EventName)
		{
			return eventNode;
		}
	}
	return NULL;
}

UAdventureCharacter* UDialogGraph::GetDialogPlayerCharacterInstance(UAdventurePluginGameContext* GameContext)
{
	return GetSpeakerInstance(GameContext, PlayerCharacter);
}

UAdventureCharacter* UDialogGraph::GetDialogNPCCharacterInstance(UAdventurePluginGameContext* GameContext)
{
	return GetSpeakerInstance(GameContext, NPCCharacter);
}

UAdventureCharacter * UDialogGraph::GetSpeakerInstance(UAdventurePluginGameContext* GameContext, TSubclassOf<UAdventureCharacter> Speaker)
{
	if (GameContext == nullptr || !GameContext->IsValidLowLevel() ||
		GameContext->AdventureCharacterManager == nullptr || !GameContext->AdventureCharacterManager->IsValidLowLevel())
	{
		// TODO: Log warning/error.
		return nullptr;
	}
	if (Speaker == nullptr)
	{
		// TODO: Log error.
		return nullptr;
	}
	auto* characterInstance = GameContext->AdventureCharacterManager->GetCharacter(Speaker);
	return characterInstance;
}

#undef LOCTEXT_NAMESPACE