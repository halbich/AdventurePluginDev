#pragma once

#include "Core.h"
#include "TextProperty.h" 
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Engine/Blueprint.h"
#include "InventoryItem.h"
#include "AdventurePluginGameContext.h"
#include "ItemManager.h"
#include "CombinableObjectBlueprint.h"
#include "InventoryItemBlueprint.generated.h"

#pragma optimize("", off)
/**
* The blueprint class for an items.
* Exists to specify the item icon.
*/
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UInventoryItemBlueprint : public UCombinableObjectBlueprint, public IIconThumbnailInterface
{
	GENERATED_BODY()

public:

	virtual UTexture2D* GetIcon() const override;
};
#pragma optimize("", on)