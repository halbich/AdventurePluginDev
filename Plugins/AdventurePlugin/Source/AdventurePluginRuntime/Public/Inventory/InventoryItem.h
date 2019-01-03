#pragma once

#include "Core.h"
#include "TextProperty.h" 
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Delegate.h"
#include "ItemCombination.h"
#include "ItemCombinationInterface.h"
#include "CombinableObject.h"
#include "InventoryItem.generated.h"

class UInventoryItemBlueprint;

UCLASS(Abstract, BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UInventoryItem : public UCombinableObject, public IIconThumbnailInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundBase* Comment;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText CommentText;

	virtual UTexture2D* GetIcon() const override
	{
		return Icon;
	}
};