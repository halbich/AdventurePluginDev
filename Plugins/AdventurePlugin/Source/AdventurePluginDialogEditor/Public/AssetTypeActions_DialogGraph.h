#pragma once

#include "CoreMinimal.h"
#include "GenericGraphEditor/Private/AssetTypeActions_GenericGraph.h"

class FAssetTypeActions_DialogGraph : public FAssetTypeActions_GenericGraph
{
public:
	FAssetTypeActions_DialogGraph(EAssetTypeCategories::Type InAssetCategory);

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;	
	//virtual uint32 GetCategories() override;
};