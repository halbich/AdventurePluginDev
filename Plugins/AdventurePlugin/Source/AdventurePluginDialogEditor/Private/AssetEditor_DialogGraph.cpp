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

#undef LOCTEXT_NAMESPACE