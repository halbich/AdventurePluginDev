#include "AssetTypeActions_DialogGraph.h"
#include "DialogGraph.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_DialogGraph"

FAssetTypeActions_DialogGraph::FAssetTypeActions_DialogGraph(EAssetTypeCategories::Type InAssetCategory)
	: FAssetTypeActions_GenericGraph(InAssetCategory)
{
}

FText FAssetTypeActions_DialogGraph::GetName() const
{
	return LOCTEXT("FDialogGraphAssetTypeActionsName", "Dialog Graph");
}

FColor FAssetTypeActions_DialogGraph::GetTypeColor() const
{
	return FColor(255, 160, 240);
}

UClass* FAssetTypeActions_DialogGraph::GetSupportedClass() const
{
	return UDialogGraph::StaticClass();
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE