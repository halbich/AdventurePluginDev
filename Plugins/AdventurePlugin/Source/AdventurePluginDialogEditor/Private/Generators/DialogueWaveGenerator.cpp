#include "Generators/DialogueWaveGenerator.h"
#include "Dialog/Graph/DialogGraph.h"
#include "Dialog/Graph/DialogGraphNode.h"
#include "Dialog/Graph/BaseClasses/DialogGraphNode_DialogLineBase.h"
#include "AdventureCharacter.h"
#include "Factories/DialogueWaveFactory.h"
#include "Factories/DialogueVoiceFactory.h"
#include "Sound/DialogueWave.h"
#include "Sound/DialogueVoice.h"
#include "AssetRegistryModule.h"
#include "FileHelpers.h"

void FDialogueWaveGenerator::GenerateDialogueWaves()
{
	// Get, and if necessary, initialize, references to characters and voices of both participants of the dialogue.
	PlayerCharacter = Cast<UAdventureCharacter>(Graph->PlayerCharacter ? Graph->PlayerCharacter->ClassDefaultObject : nullptr);
	NpcCharacter = Cast<UAdventureCharacter>(Graph->NPCCharacter ? Graph->NPCCharacter->ClassDefaultObject : nullptr);
	PlayerVoice = PlayerCharacter ? GetDialogueVoiceOfCharacter(PlayerCharacter) : nullptr;
	NpcVoice = NpcCharacter ? GetDialogueVoiceOfCharacter(NpcCharacter) : nullptr;
	for (UGenericGraphNode* Node : Graph->AllNodes)
	{
		UDialogGraphNode_DialogLineBase* DialogNode = Cast<UDialogGraphNode_DialogLineBase>(Node);
		if (!IsValid(DialogNode))
		{
			continue;
		}
		UpdateDialogueWaveForDialogueNode(DialogNode);
	}
	// Quite likely a lot of other packages changed as well. We could technically keept a list and save only those modified by the save, but...
	// This is easier and fool proof. But we should probably change it at some point, hence the next line.
	// TODO: Save only those assets affected by dialog generation.
	UEditorLoadingAndSavingUtils::SaveDirtyPackagesWithDialog(false, true);
}

void FDialogueWaveGenerator::UpdateDialogueWaveForDialogueNode(UDialogGraphNode_DialogLineBase* DialogNode)
{
	// Generate the node if it does not exist yet in the correct location.
	// TODO: Rename.
	if (!IsValid(DialogNode->DialogueWave) || !IsDialogueWaveNameCorrect(DialogNode))
	{
		GenerateDialogueWaveForNode(DialogNode);
	}
	// Figure out who is the speaker and who is the target
	bool isPlayerLine = PlayerCharacter == DialogNode->GetSpeakerEditorOnly();
	auto* speakerVoice = isPlayerLine ? PlayerVoice : NpcVoice;
	auto* targetVoice = isPlayerLine ? NpcVoice : PlayerVoice;
	// Check if the mapping is fine - the Dialogue Wave is a bit more general, supports more voices and targets, which we do not support. 
	auto* dialogueWave = DialogNode->DialogueWave;
	if (dialogueWave->ContextMappings.Num() != 1)
	{
		check(false && "Dialogue waves with more than one context are not supported");
		return;
	}
	auto& mapping = dialogueWave->ContextMappings[0];
	check(mapping.Context.Targets.Num() < 2 && "We do not support more than one target currently.");
	// The voice that was used before this save, or null if we were not using anything.
	UDialogueVoice* oldTargetVoice = mapping.Context.Targets.Num() > 0 ? mapping.Context.Targets[0] : nullptr;
	// Go field by field, if anything changed anything is different in the package compared to the graph,
	// replace it with the graph version and mark the dialogue node as dirty.
	if (mapping.Context.Speaker != speakerVoice || oldTargetVoice != targetVoice || mapping.SoundWave != DialogNode->DialogSound)
	{
		// Context can only be replaced as a whole, so we check it as a whole.
		dialogueWave->UpdateContext(mapping, DialogNode->DialogSound, speakerVoice, { targetVoice });
		dialogueWave->MarkPackageDirty();
	}
	// The localization key that should be used for this node.
	FString localizationKey = Graph->Name + "." + DialogNode->Id.ToString();
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

void FDialogueWaveGenerator::GenerateDialogueWaveForNode(UDialogGraphNode_DialogLineBase* Node)
{
	// Initilize the package in which the wave will be saving the object.
	auto path = GetDialogueWavePath(Node);
	auto* package = CreatePackage(nullptr, *path);
	// Use a factory to ensure we are creating the wave properly.
	auto* dialogueWaveFactory = NewObject<UDialogueWaveFactory>();
	auto* newWave = dialogueWaveFactory->FactoryCreateNew(UDialogueWave::StaticClass(), package, Node->Id, RF_Standalone | RF_Public, nullptr, GWarn);
	auto* newWaveCasted = Cast<UDialogueWave>(newWave);
	// Next five lines are boilerplate internet claims is necessary for proper asset initialization.
	FAssetRegistryModule::AssetCreated(newWaveCasted);
	package->FullyLoad();
	package->SetDirtyFlag(true);
	newWaveCasted->PreEditChange(NULL);
	newWaveCasted->PostEditChange();
	// Set the reference to the created node. No need to mark the node as dirty, as we are right now in the middle of saving the graph.
	Node->DialogueWave = newWaveCasted;
}

bool FDialogueWaveGenerator::IsDialogueWaveNameCorrect(UDialogGraphNode_DialogLineBase* Node)
{
	if (!IsValid(Node) || !IsValid(Graph) || !IsValid(Node->DialogueWave))
	{
		return false;
	}
	// Get the path to the package and check if it follows the correct scheme, i.e. /Game/Generated/Graph/Node
	auto correctPath = GetDialogueWavePath(Node);
	auto currentPath = Node->DialogueWave->GetOuter()->GetName();
	return correctPath.Equals(currentPath);
}


FString FDialogueWaveGenerator::GetDialogueWavePath(UDialogGraphNode_DialogLineBase* Node)
{
	return "/Game/Generated/" + Graph->Name + "/" + Node->Id.ToString();
}

UDialogueVoice* FDialogueWaveGenerator::GetDialogueVoiceOfCharacter(UAdventureCharacter* Character)
{
	// TODO: This should probably be moved and generated when we save the adventure character.
	if (Character->Voice == nullptr)
	{
		// The voice was probably not created yet - whatever the reason for that was, recreate it.
		GenerateDialogueVoiceForCharacter(Character);
	}
	// Synchronize the voice with the character class
	if (Character->Plurality != Character->Voice->Plurality || Character->Gender != Character->Voice->Gender)
	{
		Character->Voice->Gender = Character->Gender;
		Character->Voice->Plurality = Character->Plurality;
		Character->Voice->MarkPackageDirty();
	}
	return Character->Voice;
}

void FDialogueWaveGenerator::GenerateDialogueVoiceForCharacter(UAdventureCharacter* Character)
{
	// First, create the package in which the voice asset should be stored
	FString path = "/Game/Generated/Voices/" + Character->Id.ToString();
	auto* package = CreatePackage(nullptr, *path);
	// Create the voice class using a factory to make sure we do not forget anything initialization related.
	auto* dialogueVoiceFactory = NewObject<UDialogueVoiceFactory>();
	auto* newVoice = dialogueVoiceFactory->FactoryCreateNew(UDialogueVoice::StaticClass(), package, Character->Id, RF_Standalone | RF_Public, nullptr, GWarn);
	auto* newVoiceCasted = Cast<UDialogueVoice>(newVoice);
	// Next five lines are boilerplate that internet says is necessary to initialize the asset correctly.
	FAssetRegistryModule::AssetCreated(newVoiceCasted);
	package->FullyLoad();
	package->SetDirtyFlag(true);
	newVoiceCasted->PreEditChange(NULL);
	newVoiceCasted->PostEditChange();
	// Set the new voice on the character.
	Character->Voice = newVoiceCasted;
	Character->MarkPackageDirty();
}

