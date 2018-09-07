#include "AssetEditor_QuestGraph.h"
#include "AssetGraphSchema_QuestGraph.h"

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

#undef LOCTEXT_NAMESPACE