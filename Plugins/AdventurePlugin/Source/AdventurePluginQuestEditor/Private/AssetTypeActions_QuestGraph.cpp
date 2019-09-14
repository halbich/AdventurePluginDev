#include "AssetTypeActions_QuestGraph.h"
#include "AssetEditor_QuestGraph.h"
#include "Quest/Graph/QuestGraph.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_QuestGraph"

FAssetTypeActions_QuestGraph::FAssetTypeActions_QuestGraph(EAssetTypeCategories::Type InAssetCategory)
	: FAssetTypeActions_GenericGraph(InAssetCategory)
{
}

FText FAssetTypeActions_QuestGraph::GetName() const
{
	return LOCTEXT("FQuestGraphAssetTypeActionsName", "Quest Graph");
}

FColor FAssetTypeActions_QuestGraph::GetTypeColor() const
{
	return FColor(32, 178, 170);
}

UClass* FAssetTypeActions_QuestGraph::GetSupportedClass() const
{
	return UQuestGraph::StaticClass();
}

void FAssetTypeActions_QuestGraph::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;	
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UQuestGraph* Graph = Cast<UQuestGraph>(*ObjIt))
		{
			TSharedRef<FAssetEditor_QuestGraph> NewGraphEditor(new FAssetEditor_QuestGraph());
			NewGraphEditor->InitGenericGraphAssetEditor(Mode, EditWithinLevelEditor, Graph);
		}
	}
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE