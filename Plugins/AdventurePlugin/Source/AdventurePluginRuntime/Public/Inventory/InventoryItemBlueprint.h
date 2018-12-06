#pragma once

#include "Core.h"
#include "TextProperty.h" 
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Engine/Blueprint.h"
#include "InventoryItem.h"
#include "AdventurePluginGameContext.h"
#include "ItemManager.h"
#include "InventoryItemBlueprint.generated.h"

#pragma optimize("", off)
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UInventoryItemBlueprint : public UBlueprint, public IIconThumbnailInterface
{
	GENERATED_BODY()

public:

	virtual UTexture2D* GetIcon() const override;

	UFUNCTION(BlueprintCallable)
	UInventoryItem* GetItemInstance(UAdventurePluginGameContext* GameContext);
};
#pragma optimize("", on)