#include "AssetEditor_DialogGraph.h"
#include "AssetGraphSchema_DialogGraph.h"

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

#undef LOCTEXT_NAMESPACE