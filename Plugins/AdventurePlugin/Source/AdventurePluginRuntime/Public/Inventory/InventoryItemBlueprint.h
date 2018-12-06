#pragma once

#include "Core.h"
#include "TextProperty.h" 
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Engine/Blueprint.h"
#include "InventoryItem.h"
#include "InventoryItemBlueprint.generated.h"

UCLASS()
class ADVENTUREPLUGINRUNTIME_API UInventoryItemBlueprint : public UBlueprint, public IIconThumbnailInterface
{
	GENERATED_BODY()

public:

	virtual UTexture2D* GetIcon() const override
	{
		// TODO For MattK
		// Je nutno vr�tit "UTexture2D* Icon", kter� je na UInventoryItem, kter� je Parent classa tohohle blueprintu
		
		return nullptr;
	}
};