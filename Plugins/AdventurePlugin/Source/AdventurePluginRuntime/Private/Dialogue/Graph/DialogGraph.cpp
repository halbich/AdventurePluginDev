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

UAdventureCharacter* UDialogGraph::GetDialogPlayerCharacterInstance(UAdventurePluginGameContext* Context)
{
	return GetSpeakerInstance(Context, PlayerCharacter);
}

UAdventureCharacter* UDialogGraph::GetDialogNPCCharacterInstance(UAdventurePluginGameContext* Context)
{
	return GetSpeakerInstance(Context, NPCCharacter);
}

UAdventureCharacter * UDialogGraph::GetSpeakerInstance(UAdventurePluginGameContext* Context, TSubclassOf<UAdventureCharacter> Speaker)
{
	if (Context == nullptr || !Context->IsValidLowLevel() ||
		Context->AdventureCharacterManager == nullptr || !Context->AdventureCharacterManager->IsValidLowLevel())
	{
		// TODO: Log warning/error.
		return nullptr;
	}
	if (Speaker == nullptr)
	{
		// TODO: Log error.
		return nullptr;
	}
	auto* characterInstance = Context->AdventureCharacterManager->GetCharacter(Speaker);
	return characterInstance;
}

#undef LOCTEXT_NAMESPACE