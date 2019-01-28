#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "InventoryItemState.generated.h"

UENUM(BlueprintType)	
enum class EInventoryItemState : uint8
{
	ItemState_NotSpawned 		UMETA(DisplayName = "Not Spawned"),
	ItemState_Spawned			UMETA(DisplayName = "Spawned"),
	ItemState_InInventory	 	UMETA(DisplayName = "In Inventory"),
	ItemState_Used				UMETA(DisplayName = "Used"),
	ItemState_Custom		 	UMETA(DisplayName = "Custom"),
};