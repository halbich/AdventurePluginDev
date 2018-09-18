#pragma once

#include "Core.h"
#include "Classes/Engine/DataAsset.h"
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "InventoryItem.generated.h"

UCLASS(BlueprintType)
class ADVENTUREPLUGINRUNTIME_API UInventoryItem : public UDataAsset, public IIconThumbnailInterface
{
	//GENERATED_USTRUCT_BODY()
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;

	virtual UTexture2D* GetIcon() const override
	{
		return Icon;
	}
};