#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_EntryMain.h"
#include "DialogGraphNode_Event.h"
#include "AdventurePluginGameContext.h"
#include "AdventureCharacterManager.h"
#include "AdventurePluginRuntime.h"
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
		LOG_Warning(NSLOCTEXT("AP", "GetSpeakerInstanceSpeakerNull", "DialogGraph:GetSpeakerInstance: The speaker is null."));
		return nullptr;
	}
	UAdventureCharacter* CharacterInstance = GameContext->AdventureCharacterManager->GetCharacter(Speaker);
	return CharacterInstance;
}

#undef LOCTEXT_NAMESPACE