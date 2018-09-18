#pragma once

#include "Core.h"
#include "AdventureCharacter.h"
#include "AssetTypeActions_Base.h"

class FAssetTypeActions_AdventureCharacter : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_AdventureCharacter(EAssetTypeCategories::Type InAssetCategory)
		: MyAssetCategory(InAssetCategory)
	{
	}

	virtual FText GetName() const override 
	{ 
		return NSLOCTEXT("AssetTypeActions_AdventureCharacter", "AssetName", "Adventure Character"); 
	}

	virtual FColor GetTypeColor() const override
	{
		return FColor(127, 255, 255);
	}

	virtual UClass* GetSupportedClass() const override
	{
		return UAdventureCharacter::StaticClass();
	}

	virtual uint32 GetCategories() override 
	{ 
		return MyAssetCategory; 
	}

	virtual FText GetAssetDescription(const FAssetData &AssetData) const override 
	{ 
		return NSLOCTEXT("AssetTypeActions_AdventureCharacter", "AssetDescription", "Adventure Character"); 
	}

	virtual class UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override
	{
		return nullptr;
	}

private:
	EAssetTypeCategories::Type MyAssetCategory;
};