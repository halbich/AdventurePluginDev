/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
* Asset action for creating a graph asset of type UGenericGraph.
* @see UGenericGraph
*/
class ADVENTUREPLUGINEDITOR_API FAssetTypeActions_GenericGraph : public FAssetTypeActions_Base
{
public:

	/**
	* @param InAssetCategory Asset categories of this asset
	*/
	FAssetTypeActions_GenericGraph(EAssetTypeCategories::Type InAssetCategory);

	/** Returns the name of this type */
	virtual FText GetName() const override;

	/** Returns the color associated with this type */
	virtual FColor GetTypeColor() const override;

	/**
	* Checks to see if the specified object is handled by this type.
	* @return Asset type, in default case UGenericGraph
	*/
	virtual UClass* GetSupportedClass() const override;

	/** Opens the asset editor for the specified objects. If EditWithinLevelEditor is valid, the world-centric editor will be used. */
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

	/** Returns the categories of this asset type. The return value is one or more flags from EAssetTypeCategories.  */
	virtual uint32 GetCategories() override;

private:

	/** Asset categories of this asset */
	EAssetTypeCategories::Type MyAssetCategory;
};