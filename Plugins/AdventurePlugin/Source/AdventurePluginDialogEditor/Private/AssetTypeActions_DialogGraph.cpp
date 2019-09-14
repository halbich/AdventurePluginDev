#include "AssetTypeActions_DialogGraph.h"
#include "AssetEditor_DialogGraph.h"
#include "Dialog/Graph/DialogGraph.h"

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

void FAssetTypeActions_DialogGraph::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;	
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UDialogGraph* Graph = Cast<UDialogGraph>(*ObjIt))
		{
			TSharedRef<FAssetEditor_DialogGraph> NewGraphEditor(new FAssetEditor_DialogGraph());
			NewGraphEditor->InitGenericGraphAssetEditor(Mode, EditWithinLevelEditor, Graph);
		}
	}
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE