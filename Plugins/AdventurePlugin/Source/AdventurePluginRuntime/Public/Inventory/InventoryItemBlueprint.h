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
		// Je nutno vrátit "UTexture2D* Icon", která je na UInventoryItem, který je Parent classa tohohle blueprintu
		
		return nullptr;
	}
};