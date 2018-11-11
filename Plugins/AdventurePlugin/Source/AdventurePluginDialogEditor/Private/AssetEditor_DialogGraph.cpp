#include "AssetEditor_DialogGraph.h"
#include "AssetGraphSchema_DialogGraph.h"
#include "DialogGraphNode_EntryMain.h"

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
		auto* entryPointNode = Cast<UDialogGraphNode_EntryMain>(node);
		if (entryPointNode) {
			editingDialogGraph->MainEntryPoint = entryPointNode;
		}
		auto* rootDialogGraphNode = Cast<UDialogGraphNode>(node);
		FillIdToNodeMap(rootDialogGraphNode, editingDialogGraph);
	}
}

void FAssetEditor_DialogGraph::FillIdToNodeMap(UDialogGraphNode* RootNode, UDialogGraph* Graph)
{
	if (RootNode == NULL || !RootNode->IsValidLowLevel()) 
	{
		return;
	}
	if (!RootNode->Id.IsNone()) 
	{
		Graph->IdToNodeMap.Add(RootNode->Id, RootNode);
	}
	for (auto* child : RootNode->ChildrenNodes) {
		FillIdToNodeMap(Cast<UDialogGraphNode>(child), Graph);
	}
}

#undef LOCTEXT_NAMESPACE