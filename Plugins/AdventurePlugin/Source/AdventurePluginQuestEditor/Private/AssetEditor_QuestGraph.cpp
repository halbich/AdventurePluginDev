#include "AssetEditor_QuestGraph.h"
#include "AssetGraphSchema_QuestGraph.h"
#include "QuestGraphNode_End.h"


#define LOCTEXT_NAMESPACE "AssetEditor_QuestGraph"

FGraphAppearanceInfo FAssetEditor_QuestGraph::GetViewportWidgetAppearanceInfo() const
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText_QuestGraph", "QUEST GRAPH");
	return AppearanceInfo;
}

UClass* FAssetEditor_QuestGraph::GetGraphSchemaClass() const
{
	return UAssetGraphSchema_QuestGraph::StaticClass();
}

void FAssetEditor_QuestGraph::RebuildGenericGraph() {
	FAssetEditor_GenericGraph::RebuildGenericGraph();
	auto * editingQuestGraph = Cast<UQuestGraph>(EditingGraph);
	if (editingQuestGraph == nullptr)
	{
		return;
	}
	editingQuestGraph->EndNode = nullptr;
	for (auto* node : editingQuestGraph->AllNodes) {
		if (node != nullptr && node->IsValidLowLevel() && node->GetClass()->IsChildOf<UQuestGraphNode_End>()) 
		{
			editingQuestGraph->EndNode = Cast<UQuestGraphNode>(node);
			break;
		}
	}
}

#undef LOCTEXT_NAMESPACE