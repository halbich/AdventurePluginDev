#include "AssetEditor_DialogGraph.h"
#include "AssetGraphSchema_DialogGraph.h"
#include "DialogGraphNode_EntryMain.h"
#include "DialogGraphNode_EntrySecondary.h"

#define LOCTEXT_NAMESPACE "AssetEditor_DialogGraph"

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
void FAssetEditor_DialogGraph::RebuildGenericGraph() {
	FAssetEditor_GenericGraph::RebuildGenericGraph();
	auto * editingDialogGraph = Cast<UDialogGraph>(EditingGraph);
	if (editingDialogGraph == nullptr)
	{
		return;
	}
	editingDialogGraph->IdToNodeMap.Empty();
	for (auto* node : editingDialogGraph->RootNodes) {
		auto* mainEntryPoint = Cast<UDialogGraphNode_EntryMain>(node);
		if (mainEntryPoint != nullptr && mainEntryPoint->IsValidLowLevel()) {
			editingDialogGraph->MainEntryPoint = mainEntryPoint;
			continue;
		}
		auto* secondaryEntryPoint = Cast<UDialogGraphNode_EntrySecondary>(node);
		if (secondaryEntryPoint != nullptr && secondaryEntryPoint->IsValidLowLevel() && !secondaryEntryPoint->Id.IsNone())
		{
			editingDialogGraph->SecondaryEntryPoints.Add(secondaryEntryPoint->Id, secondaryEntryPoint);
			continue;
		}
		// TODO: Unknown root node. Should we throw something? Or assume it's an extension and everything's alright?
	}
	FillIdToNodeMap(editingDialogGraph);
}

void FAssetEditor_DialogGraph::FillIdToNodeMap(UDialogGraph* Graph)
{
	for (auto* node : Graph->AllNodes)
	{
		auto* dialogNode = Cast<UDialogGraphNode>(node);
		if (dialogNode == NULL || !dialogNode->IsValidLowLevel())
		{
			continue;
		}
		if (!dialogNode->Id.IsNone())
		{
			Graph->IdToNodeMap.Add(dialogNode->Id, dialogNode);
		}
	}
}

#undef LOCTEXT_NAMESPACE