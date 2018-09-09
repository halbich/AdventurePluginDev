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
	for (auto* node : editingDialogGraph->RootNodes) {
		auto* entryPointNode = Cast<UDialogGraphNode_EntryMain>(node);
		if (entryPointNode) {
			editingDialogGraph->MainEntryPoint = entryPointNode;
		}
	}
}

#undef LOCTEXT_NAMESPACE