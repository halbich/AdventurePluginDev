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
	UQuestGraph * EditingQuestGraph = Cast<UQuestGraph>(EditingGraph);
	if (EditingQuestGraph == nullptr)
	{
		return;
	}
	EditingQuestGraph->EndNode = nullptr;
	for (UGenericGraphNode* Node : EditingQuestGraph->AllNodes) {
		if (IsValid(Node) && Node->GetClass()->IsChildOf<UQuestGraphNode_End>())
		{
			EditingQuestGraph->EndNode = Cast<UQuestGraphNode>(Node);
			break;
		}
	}
}

#undef LOCTEXT_NAMESPACE