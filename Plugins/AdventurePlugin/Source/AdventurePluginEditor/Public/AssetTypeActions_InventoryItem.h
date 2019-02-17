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

	virtual FText GetName() const override 
	{ 
		return NSLOCTEXT("AssetTypeActions_InventoryItem", "AssetName", "Inventory Item"); 
	}

	virtual FColor GetTypeColor() const override
	{
		return FColor(0, 0, 180);
	}

	virtual UClass* GetSupportedClass() const override
	{
		return UInventoryItem::StaticClass();
	}

	virtual uint32 GetCategories() override 
	{ 
		return MyAssetCategory; 
	}

	virtual FText GetAssetDescription(const FAssetData &AssetData) const override 
	{ 
		return NSLOCTEXT("AssetTypeActions_InventoryItem", "AssetDescription", "Inventory Item"); 
	}

	virtual class UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override
	{
		return nullptr;
	}

private:
	EAssetTypeCategories::Type MyAssetCategory;
};