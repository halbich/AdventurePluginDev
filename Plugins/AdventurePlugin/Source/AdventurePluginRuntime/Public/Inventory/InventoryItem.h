#pragma once

#include "Core.h"
#include "TextProperty.h" 
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Delegate.h"
#include "SimpleCombination.h"
#include "CombinationInterface.h"
#include "CombinableObject.h"
#include "Dialogue/Structs/DialogGraphEntryPoint.h"
#include "InventoryItemState.h"
#include "InventoryItem.generated.h"

class UInventoryItemBlueprint;

UCLASS(Abstract, BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UInventoryItem : public UCombinableObject, public IIconThumbnailInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FDialogGraphEntryPoint Dialog;
	//TODO: Create nice picker for Tags that loads options from settings.
	/* Tags assigned to this item, e.g. weapon, critical, red herring etc. No inherent function unless designers make it so*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSet<FName> Tags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EInventoryItemState ItemState;

	virtual UTexture2D* GetIcon() const override
	{
		return Icon;
	}

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		virtual bool WasPickedUp()
	{
		return ItemState != EInventoryItemState::ItemState_NotSpawned && ItemState != EInventoryItemState::ItemState_Spawned;
	}
};