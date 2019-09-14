#pragma once

#include "CoreMinimal.h"
#include "UObject/TextProperty.h" 
#include "Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Engine/Blueprint.h"
#include "InventoryItem.h"
#include "Common/AdventurePluginGameContext.h"
#include "ItemManager.h"
#include "Combinations/CombinableObjectBlueprint.h"
#include "InventoryItemBlueprint.generated.h"

/**
* The blueprint class for inventory items. This class exists to specify the item icon
* and to give user a possibility to define custom behavior of the item.
* @see UInventoryItemFactory
*/
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UInventoryItemBlueprint : public UCombinableObjectBlueprint, public IIconThumbnailInterface
{
	GENERATED_BODY()

public:

	virtual UTexture2D* GetIcon() const override;
};