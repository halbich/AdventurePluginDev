#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/AssetTypeActions_GenericGraph.h"

/**
* Asset action for creating a dialog graph asset of type UDialogGraph.
* @see UDialogGraph
*/
class FAssetTypeActions_DialogGraph : public FAssetTypeActions_GenericGraph
{
public:

	FAssetTypeActions_DialogGraph(EAssetTypeCategories::Type InAssetCategory);

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;	
};