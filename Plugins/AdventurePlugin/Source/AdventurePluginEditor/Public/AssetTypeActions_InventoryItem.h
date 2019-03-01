#pragma once

#include "Core.h"
#include "Inventory/InventoryItem.h"
#include "AssetTypeActions_Base.h"

/**
* Action for creating inventory item asset, which is an UInventoryItemBlueprint.
* @see UInventoryItemBlueprint
*/
class FAssetTypeActions_InventoryItem : public FAssetTypeActions_Base
{
public:

	FAssetTypeActions_InventoryItem(EAssetTypeCategories::Type InAssetCategory)
		: MyAssetCategory(InAssetCategory)
	{
	}

	/**
	* Returns the name of the asset type created with this action.
	* @return Name of the asset type
	*/
	virtual FText GetName() const override 
	{ 
		return NSLOCTEXT("AssetTypeActions_InventoryItem", "AssetName", "Inventory Item"); 
	}

	/**
	* Returns the color associated with this asset type in UE editor.
	* @return Color of this asset type
	*/
	virtual FColor GetTypeColor() const override
	{
		return FColor(0, 0, 180);
	}

	/**
	* Returns the asset type for which this action is registered.
	* @return Asset type
	*/
	virtual UClass* GetSupportedClass() const override
	{
		return UInventoryItem::StaticClass();
	}

	/**
	* Returns the asset categories in which this action will be placed.
	* @return Asset categories of this asset
	*/
	virtual uint32 GetCategories() override 
	{ 
		return MyAssetCategory; 
	}

	/**
	* Returns the description of this asset type.
	* @return Description of the asset type
	*/
	virtual FText GetAssetDescription(const FAssetData &AssetData) const override 
	{ 
		return NSLOCTEXT("AssetTypeActions_InventoryItem", "AssetDescription", "Inventory Item"); 
	}

	/**
	* Returns the info associated with rendering of the thumbnail for this asset type.
	* In this case, the thumbnail info is not used.
	* @return Info for thumbnail rendering
	*/
	virtual class UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override
	{
		return nullptr;
	}

private:
	EAssetTypeCategories::Type MyAssetCategory;
};