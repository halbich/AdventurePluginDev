/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class ADVENTUREPLUGINEDITOR_API FAssetTypeActions_GenericGraph : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_GenericGraph(EAssetTypeCategories::Type InAssetCategory);

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type MyAssetCategory;
};