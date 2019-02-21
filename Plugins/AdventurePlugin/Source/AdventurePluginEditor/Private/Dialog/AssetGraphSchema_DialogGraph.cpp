#include "Dialog/AssetGraphSchema_DialogGraph.h"
#include "Dialog/Graph/DialogGraphNode_IfBool.h"
#include "Dialog/Graph/DialogGraphNode_Options.h"
#include "Dialog/Graph/DialogGraphNode_IfString.h"
#include "Dialog/Graph/DialogGraphNode_IfInteger.h"
#include "Dialog/Graph/DialogGraphNode_IfQuestFlag.h"
#include "Dialog/Graph/DialogGraphNode_IfQuestComplete.h"
#include "Dialog/Graph/DialogGraphNode_IfInInventory.h"
#include "Dialog/Graph/DialogGraphNode_EntryMain.h"
#include "Dialog/Graph/DialogGraphNode_EntrySecondary.h"
#include "Dialog/Graph/DialogGraphNode_Exit.h"
#include "Dialog/Graph/DialogGraphNode_Goto.h"
#include "Dialog/Graph/DialogGraphNode_Once.h"
#include "Dialog/Graph/BaseClasses/DialogGraphNode_TrueFalse.h"
#include "EdDialogNode_Options.h"
#include "EdDialogNode_TrueFalse.h"
#include "EdDialogNode_IfInInventory.h"
#include "EdDialogNode_NoInput.h"
#include "EdDialogNode_NoOutput.h"
#include "EdDialogNode_LessEqualMore.h"
#include "DialogGraphNode_EntryMain.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "AssetRegistryModule.h"
#include "AdventureCharacterBlueprint.h"
#include "EdGraph/EdGraph.h"

UAssetGraphSchema_DialogGraph::UAssetGraphSchema_DialogGraph()
{
	EditorNodeMap.Add(UDialogGraphNode_TrueFalse::StaticClass(),		UEdDialogNode_TrueFalse::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_IfInInventory::StaticClass(),	UEdDialogNode_TrueFalse::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_IfInteger::StaticClass(),		UEdDialogNode_LessEqualMore::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_Options::StaticClass(),			UEdDialogNode_Options::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_EntryMain::StaticClass(),		UEdDialogNode_NoInput::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_EntrySecondary::StaticClass(),	UEdDialogNode_NoInput::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_Exit::StaticClass(),				UEdDialogNode_NoOutput::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_Goto::StaticClass(),				UEdDialogNode_NoOutput::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_IfInInventory::StaticClass(),	UEdDialogNode_IfInInventory::StaticClass());
}

const FPinConnectionResponse UAssetGraphSchema_DialogGraph::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	FPinConnectionResponse Response = Super::CanCreateConnection(A, B);
	if (Response.Response == CONNECT_RESPONSE_MAKE)
	{
		Response.Response = CONNECT_RESPONSE_BREAK_OTHERS_A;
	}
	return Response;
}

void UAssetGraphSchema_DialogGraph::CreateDefaultNodesForGraph(UEdGraph& EdGraph) const
{
	FAssetSchemaAction_GenericGraph_NewNode Action;
	UDialogGraph* EditingGraph = CastChecked<UDialogGraph>(EdGraph.GetOuter());
	Action.NodeTemplate = NewObject<UEdNode_GenericGraphNode>(&EdGraph, GetEditorNodeType(UDialogGraphNode_EntryMain::StaticClass()));
	Action.NodeTemplate->GenericGraphNode = NewObject<UGenericGraphNode>(Action.NodeTemplate, UDialogGraphNode_EntryMain::StaticClass());
	Action.NodeTemplate->GenericGraphNode->Graph = EditingGraph;
	EditingGraph->MainEntryPoint = Cast<UDialogGraphNode>(Action.NodeTemplate->GenericGraphNode);
	Action.PerformAction(EditingGraph->EdGraph, nullptr, FVector2D(0, 0), false);
	// Maybe put this somewhere else? Not sure where though.
	// If there is only one player character class, use that.
	if (EditingGraph->PlayerCharacter == nullptr)
	{
		UAdventureCharacter* OnlyPlayerCharacter = GetOnlyPlayerCharacter();
		if (OnlyPlayerCharacter != nullptr)
		{
			EditingGraph->PickerPlayerCharacter = Cast<UAdventureCharacterBlueprint>(OnlyPlayerCharacter->GetClass()->ClassGeneratedBy);
			EditingGraph->PlayerCharacter = OnlyPlayerCharacter->GetClass();
		}
	}
}

TSubclassOf<UEdNode_GenericGraphNode> UAssetGraphSchema_DialogGraph::GetEditorNodeType(TSubclassOf<UGenericGraphNode> RuntimeNodeType) const
{
	if (RuntimeNodeType && RuntimeNodeType->IsChildOf(UDialogGraphNode::StaticClass()))
	{
		if (const TSubclassOf<UEdNode_GenericGraphNode>* EditorNodeType = FindEditorNodeForRuntimeNode(RuntimeNodeType))
		{
			return *EditorNodeType;
		}
	}
	return UEdDialogNode::StaticClass();
}
UAdventureCharacter* UAssetGraphSchema_DialogGraph::GetOnlyPlayerCharacter() const
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	const UClass* CharacterBlueprintClass = UAdventureCharacterBlueprint::StaticClass();
	AssetRegistryModule.Get().GetAssetsByClass(CharacterBlueprintClass->GetFName(), AssetData, true);
	// Go through all character blueprints, retrieve CDO's of classes they represent and see if they are a player character.
	UAdventureCharacter* OnlyPlayerCharacter = nullptr;
	for (FAssetData Asset : AssetData)
	{
		UAdventureCharacter* AssetCharacterObject = GetCharacterFromAsset(Asset);
		if (AssetCharacterObject == nullptr || !AssetCharacterObject->bIsPlayerCharacter)
		{
			// Not a character or not a player character
			continue;
		}
		if (OnlyPlayerCharacter != nullptr)
		{
			// Found a second player character, so we should not set anything
			return nullptr;
		}
		// Candidate for the only player character.
		OnlyPlayerCharacter = AssetCharacterObject;
	}
	return OnlyPlayerCharacter;
}

UAdventureCharacter* UAssetGraphSchema_DialogGraph::GetCharacterFromAsset(FAssetData& AssetData) const
{
#if WITH_EDITOR
	UObject* AssetObject = AssetData.GetAsset();
	UAdventureCharacterBlueprint* CharacterBlueprint = Cast<UAdventureCharacterBlueprint>(AssetObject);
	if (!IsValid(CharacterBlueprint))
	{
		return nullptr;
	}
	UObject* TargetObjectCDO = CharacterBlueprint->GeneratedClass ? CharacterBlueprint->GeneratedClass->ClassDefaultObject : nullptr;
	if (!IsValid(TargetObjectCDO))
	{
		return nullptr;
	}
	UAdventureCharacter* TargetCombinableObject = Cast<UAdventureCharacter>(TargetObjectCDO);
	if (TargetCombinableObject == nullptr)
	{
		return nullptr;
	}
	return TargetCombinableObject;
#endif
	return nullptr;
}