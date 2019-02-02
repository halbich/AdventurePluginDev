#include "Dialogue/AssetGraphSchema_DialogGraph.h"
#include "Dialogue/Graph/DialogGraphNode_IfBool.h"
#include "Dialogue/Graph/DialogGraphNode_Options.h"
#include "Dialogue/Graph/DialogGraphNode_IfString.h"
#include "Dialogue/Graph/DialogGraphNode_IfInteger.h"
#include "Dialogue/Graph/DialogGraphNode_IfQuestFlag.h"
#include "Dialogue/Graph/DialogGraphNode_IfInInventory.h"
#include "Dialogue/Graph/DialogGraphNode_EntryMain.h"
#include "Dialogue/Graph/DialogGraphNode_EntrySecondary.h"
#include "Dialogue/Graph/DialogGraphNode_Exit.h"
#include "Dialogue/Graph/DialogGraphNode_Goto.h"
#include "Dialogue/Graph/DialogGraphNode_Once.h"
#include "EdDialogNode_Options.h"
#include "EdDialogNode_TrueFalse.h"
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
	EditorNodeMap.Add(UDialogGraphNode_Once::StaticClass(),				UEdDialogNode_TrueFalse::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_IfBool::StaticClass(),			UEdDialogNode_TrueFalse::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_IfString::StaticClass(),			UEdDialogNode_TrueFalse::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_IfQuestFlag::StaticClass(),		UEdDialogNode_TrueFalse::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_IfInInventory::StaticClass(),	UEdDialogNode_TrueFalse::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_IfInteger::StaticClass(),		UEdDialogNode_LessEqualMore::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_Options::StaticClass(),			UEdDialogNode_Options::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_EntryMain::StaticClass(),		UEdDialogNode_NoInput::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_EntrySecondary::StaticClass(),	UEdDialogNode_NoInput::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_Exit::StaticClass(),				UEdDialogNode_NoOutput::StaticClass());
	EditorNodeMap.Add(UDialogGraphNode_Goto::StaticClass(),				UEdDialogNode_NoOutput::StaticClass());
}

const FPinConnectionResponse UAssetGraphSchema_DialogGraph::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	FPinConnectionResponse res = Super::CanCreateConnection(A, B);
	if (res.Response == CONNECT_RESPONSE_MAKE) res.Response = CONNECT_RESPONSE_BREAK_OTHERS_A;
	return res;
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
	//TODO: Maybe put this somewhere else? Not sure where though.
	// If there is only one player character class, use that.
	if (EditingGraph->PlayerCharacter == nullptr)
	{
		auto* onlyPlayerCharacter = GetOnlyPlayerCharacter();
		if (onlyPlayerCharacter != nullptr)
		{
			EditingGraph->PickerPlayerCharacter = Cast<UAdventureCharacterBlueprint>(onlyPlayerCharacter->GetClass()->ClassGeneratedBy);
			EditingGraph->PlayerCharacter = onlyPlayerCharacter->GetClass();
		}
	}
}

TSubclassOf<UEdNode_GenericGraphNode> UAssetGraphSchema_DialogGraph::GetEditorNodeType(TSubclassOf<UGenericGraphNode> RuntimeNodeType) const
{
	if (RuntimeNodeType && RuntimeNodeType->IsChildOf(UDialogGraphNode::StaticClass()))
	{
		TSubclassOf<UDialogGraphNode> DialogNodeType = *RuntimeNodeType;
		if (auto EditorNodeType = EditorNodeMap.Find(*DialogNodeType))
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
	const UClass* blueprintClass = UAdventureCharacterBlueprint::StaticClass();
	AssetRegistryModule.Get().GetAssetsByClass(blueprintClass->GetFName(), AssetData, true);
	// Go through all assets, retrieve CDO's of classes they represent and see if they are a player character.
	UAdventureCharacter* onlyPlayerCharacter = nullptr;
	for (auto asset : AssetData)
	{
		auto* targetObject = GetCharacterFromAsset(asset);
		if (targetObject == nullptr || !targetObject->bIsPlayerCharacter)
		{
			// Not a player character
			continue;
		}
		if (onlyPlayerCharacter != nullptr)
		{
			// Found a second player character, so we should not set anything
			return nullptr;
		}
		// Candidate for the only player character.
		onlyPlayerCharacter = targetObject;
	}
	return onlyPlayerCharacter;
}

UAdventureCharacter* UAssetGraphSchema_DialogGraph::GetCharacterFromAsset(FAssetData& AssetData) const
{
#if WITH_EDITOR
	auto* assetObject = AssetData.GetAsset();
	auto* assetCasted = Cast<UAdventureCharacterBlueprint>(assetObject);
	if (assetCasted == nullptr || !assetCasted->IsValidLowLevel())
	{
		return nullptr;
	}
	auto* assetCDO = assetCasted->GeneratedClass ? assetCasted->GeneratedClass->ClassDefaultObject : nullptr;
	if (assetCDO == nullptr || !assetCDO->IsValidLowLevel())
	{
		return nullptr;
	}
	auto* targetCombinableObject = Cast<UAdventureCharacter>(assetCDO);
	if (targetCombinableObject == nullptr)
	{
		return nullptr;
	}
	return targetCombinableObject;
#endif
	return nullptr;
}