#include "Dialog/Graph/DialogGraph.h"
#include "Dialog/Graph/DialogGraphNode.h"
#include "Dialog/Graph/DialogGraphNode_EntryMain.h"
#include "Dialog/Graph/DialogGraphNode_Event.h"
#include "Common/AdventurePluginGameContext.h"
#include "Combinations/CombinableObjectManager.h"
#include "AdventurePluginRuntime.h"

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
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("DialogGraph:GetSpeakerInstance")))
	{
		return nullptr;
	}
	if (Speaker == nullptr)
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraph_GetSpeakerInstance_SpeakerNull", "DialogGraph:GetSpeakerInstance: The speaker is null."));
		return nullptr;
	}
	
	UAdventureCharacter* CharacterInstance = Cast<UAdventureCharacter>(GameContext->CombinableObjectManager->GetCombinableObjectInstance(Speaker, this));
	return CharacterInstance;
}

#undef LOCTEXT_NAMESPACE