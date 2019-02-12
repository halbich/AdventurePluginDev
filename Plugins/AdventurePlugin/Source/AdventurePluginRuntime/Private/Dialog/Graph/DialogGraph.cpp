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
	for (UGenericGraphNode* Node : AllNodes)
	{
		UDialogGraphNode_Event* EventNode = Cast<UDialogGraphNode_Event>(Node);
		if (EventNode != nullptr && EventNode->IsValidLowLevel() && EventNode->Event.EventName == EventName)
		{
			return EventNode;
		}
	}
	return nullptr;
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
	UAdventureCharacter* CharacterInstance = GameContext->AdventureCharacterManager->GetCharacter(Speaker);
	return CharacterInstance;
}

#undef LOCTEXT_NAMESPACE