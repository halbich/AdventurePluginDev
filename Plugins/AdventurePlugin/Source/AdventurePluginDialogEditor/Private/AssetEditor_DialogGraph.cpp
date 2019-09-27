#include "AssetEditor_DialogGraph.h"
#include "AssetGraphSchema_DialogGraph.h"
#include "Dialog/Graph/DialogGraphNode_EntryMain.h"
#include "Dialog/Graph/BaseClasses/DialogGraphNode_DialogLineBase.h"
#include "Sound/DialogueWave.h"
#include "Factories/DialogueWaveFactory.h"
#include "Factories/DialogueVoiceFactory.h"
#include "AssetRegistryModule.h"
#include "FileHelpers.h"
#include "AdventureCharacter.h"
#include "Dialog/Graph/DialogGraphNode_EntrySecondary.h"

#define LOCTEXT_NAMESPACE "AssetEditor_DialogGraph"
#pragma optimize("", off)

FGraphAppearanceInfo FAssetEditor_DialogGraph::GetViewportWidgetAppearanceInfo() const
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText_DialogGraph", "DIALOG GRAPH");
	return AppearanceInfo;
}

UClass* FAssetEditor_DialogGraph::GetGraphSchemaClass() const
{
	return UAssetGraphSchema_DialogGraph::StaticClass();
}

void FAssetEditor_DialogGraph::RebuildGenericGraph()
{
	FAssetEditor_GenericGraph::RebuildGenericGraph();
	UDialogGraph * EditingDialogGraph = Cast<UDialogGraph>(EditingGraph);
	if (EditingDialogGraph == nullptr)
	{
		return;
	}
	EditingDialogGraph->IdToNodeMap.Empty();
	// Find all entry points and put them in a map, so we can have a quick access to entry points by name.
	for (UGenericGraphNode* Node : EditingDialogGraph->RootNodes)
	{
		UDialogGraphNode_EntryMain* MainEntryPoint = Cast<UDialogGraphNode_EntryMain>(Node);
		if (IsValid(MainEntryPoint))
		{
			EditingDialogGraph->MainEntryPoint = MainEntryPoint;
			continue;
		}
		UDialogGraphNode_EntrySecondary* SecondaryEntryPoint = Cast<UDialogGraphNode_EntrySecondary>(Node);
		if (IsValid(SecondaryEntryPoint) && !SecondaryEntryPoint->Id.IsNone())
		{
			EditingDialogGraph->SecondaryEntryPoints.Add(SecondaryEntryPoint->Id, SecondaryEntryPoint);
			continue;
		}
		// Unknown root node. While that is unexpected and not supported, it is concievable some extension might use root nodes unknown to us.
	}
	FillIdToNodeMap(EditingDialogGraph);
	GenerateDialogueWaves(EditingDialogGraph);
}

void FAssetEditor_DialogGraph::FillIdToNodeMap(UDialogGraph* Graph)
{
	for (UGenericGraphNode* Node : Graph->AllNodes)
	{
		UDialogGraphNode* DialogNode = Cast<UDialogGraphNode>(Node);
		if (!IsValid(DialogNode))
		{
			continue;
		}
		if (!DialogNode->Id.IsNone())
		{
			Graph->IdToNodeMap.Add(DialogNode->Id, DialogNode);
		}
	}
}

void FAssetEditor_DialogGraph::GenerateDialogueWaves(UDialogGraph* Graph)
{
	auto* playerCharacter = Graph->PlayerCharacter ? Graph->PlayerCharacter->ClassDefaultObject : nullptr;
	auto* playerVoice = Graph->PlayerCharacter ? GetDialogueVoiceOfCharacter(Cast<UAdventureCharacter>(Graph->PlayerCharacter->ClassDefaultObject)) : nullptr;
	auto* npcVoice = Graph->NPCCharacter ? GetDialogueVoiceOfCharacter(Cast<UAdventureCharacter>(Graph->NPCCharacter->ClassDefaultObject)) : nullptr;
	for (UGenericGraphNode* Node : Graph->AllNodes)
	{
		UDialogGraphNode_DialogLineBase* DialogNode = Cast<UDialogGraphNode_DialogLineBase>(Node);
		if (!IsValid(DialogNode))
		{
			continue;
		}
		if (!IsValid(DialogNode->DialogueWave) || !IsDialogueWaveNameCorrect(Graph, DialogNode))
		{
			GenerateDialogueWaveForNode(Graph, DialogNode);
		}
		bool isPlayerLine = playerCharacter == DialogNode->GetSpeakerEditorOnly();
		auto* speakerVoice = isPlayerLine ? playerVoice: npcVoice;
		auto* targetVoice = isPlayerLine ? npcVoice : playerVoice;
		auto* dialogueWave = DialogNode->DialogueWave;
		if (dialogueWave->ContextMappings.Num() != 1)
		{
			check(false && "Dialogue waves with more than one context are not supported");
			continue;
		}
		auto& mapping = dialogueWave->ContextMappings[0];
		check (mapping.Context.Targets.Num() < 2 && "We do not support more than one target currently.");
		UDialogueVoice* oldTargetVoice = mapping.Context.Targets.Num() > 0 ? mapping.Context.Targets[0] : nullptr;
		FString localizationKey = Graph->Name + "." + DialogNode->Id.ToString();
		if (mapping.Context.Speaker != speakerVoice || oldTargetVoice != targetVoice || mapping.SoundWave != DialogNode->DialogSound)
		{
			dialogueWave->UpdateContext(mapping, DialogNode->DialogSound, speakerVoice, { targetVoice });
			dialogueWave->MarkPackageDirty();
		}
		if (mapping.LocalizationKeyFormat != localizationKey)
		{
			mapping.LocalizationKeyFormat = localizationKey;
			dialogueWave->MarkPackageDirty();
		}
		if (dialogueWave->VoiceActorDirection != DialogNode->Note.ToString())
		{
			dialogueWave->VoiceActorDirection = DialogNode->Note.ToString();
			dialogueWave->MarkPackageDirty();
		}
		if (dialogueWave->SpokenText != DialogNode->DialogText.ToString())
		{
			dialogueWave->SpokenText = DialogNode->DialogText.ToString();
			dialogueWave->MarkPackageDirty();
		}
	}
	//FEditorFileUtils::PromptForCheckoutAndSave(createdPackages, bCheckDirty, bPromptToSave);
}

void FAssetEditor_DialogGraph::GenerateDialogueWaveForNode(UDialogGraph* Graph, UDialogGraphNode_DialogLineBase* Node)
{
	auto* dialogueWaveFactory = NewObject<UDialogueWaveFactory>();
	auto path = GetDialogueWavePath(Graph, Node);
	auto* package = CreatePackage(nullptr, *path);

	auto* newWave = dialogueWaveFactory->FactoryCreateNew(UDialogueWave::StaticClass(), package, Node->Id, RF_Standalone | RF_Public, nullptr, GWarn);
	auto* NewWaveCasted = Cast<UDialogueWave>(newWave);
	FAssetRegistryModule::AssetCreated(NewWaveCasted);
	package->FullyLoad();
	package->SetDirtyFlag(true);
	NewWaveCasted->PreEditChange(NULL);
	NewWaveCasted->PostEditChange();
	Node->DialogueWave = NewWaveCasted;
}

bool FAssetEditor_DialogGraph::IsDialogueWaveNameCorrect(UDialogGraph* Graph, UDialogGraphNode_DialogLineBase* Node)
{
	if (!IsValid(Node) || !IsValid(Graph) || !IsValid(Node->DialogueWave)) 
	{
		return false;
	}
	auto correctPath = GetDialogueWavePath(Graph, Node);
	auto newPath = Node->DialogueWave->GetOuter()->GetName();
	return correctPath.Equals(newPath);

}


FString FAssetEditor_DialogGraph::GetDialogueWavePath(UDialogGraph* Graph, UDialogGraphNode_DialogLineBase* Node)
{
	FString path = "/Game/Generated/";
	path.Append(Graph->Name);
	path.Append("/");
	path.Append(Node->Id.ToString());
	return path;
}

UDialogueVoice* FAssetEditor_DialogGraph::GetDialogueVoiceOfCharacter(UAdventureCharacter* Character)
{
	if (Character->Voice == nullptr)
	{
		GenerateDialogueVoiceForCharacter(Character);
	}
	if (Character->Plurality != Character->Voice->Plurality || Character->Gender != Character->Voice->Gender) 
	{
		Character->Voice->Gender = Character->Gender;
		Character->Voice->Plurality = Character->Plurality;
		Character->Voice->MarkPackageDirty();
	}
	return Character->Voice;
}
void FAssetEditor_DialogGraph::GenerateDialogueVoiceForCharacter(UAdventureCharacter* Character)
{
	auto* dialogueVoiceFactory = NewObject<UDialogueVoiceFactory>();
	FString path = "/Game/Generated/Voices/";
	path.Append(Character->Id.ToString());
	auto* package = CreatePackage(nullptr, *path);

	auto* newVoice = dialogueVoiceFactory->FactoryCreateNew(UDialogueVoice::StaticClass(), package, Character->Id, RF_Standalone | RF_Public, nullptr, GWarn);
	auto* newVoiceCasted = Cast<UDialogueVoice>(newVoice);
	FAssetRegistryModule::AssetCreated(newVoiceCasted);
	package->FullyLoad();
	package->SetDirtyFlag(true);
	newVoiceCasted->PreEditChange(NULL);
	newVoiceCasted->PostEditChange();
	Character->Voice = newVoiceCasted;
	Character->MarkPackageDirty();
}

#undef LOCTEXT_NAMESPACE
#pragma optimize("", on)