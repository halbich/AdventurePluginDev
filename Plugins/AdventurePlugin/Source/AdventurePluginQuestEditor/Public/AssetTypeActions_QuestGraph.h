#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/AssetTypeActions_GenericGraph.h"

/**
* Asset action for opening a quest graph.
* @see UQuestGraph
*/
class FAssetTypeActions_QuestGraph : public FAssetTypeActions_GenericGraph
{
public:
	FAssetTypeActions_QuestGraph(EAssetTypeCategories::Type InAssetCategory);

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;	
};