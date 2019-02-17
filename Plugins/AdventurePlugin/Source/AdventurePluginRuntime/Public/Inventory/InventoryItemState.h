#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "InventoryItemState.generated.h"
/**
* All the possible states of an item
* This is really basic for normal lifetime of an item.
* Not spawned when the item has not even appeared yet.
* Spawned when it appeared on the scene.
* InInventory when it was picked up.
* Used when it was used and disappeared, either from scene or inventory.
* If an item needs something little more advanced, it can use the custom state.
* Invalid state is here to for serialization errors. Should never appear in runtime.
*/
UENUM(BlueprintType)	
enum class EInventoryItemState : uint8
{
	ItemState_NotSpawned 		UMETA(DisplayName = "Not Spawned"),
	ItemState_Spawned			UMETA(DisplayName = "Spawned"),
	ItemState_InInventory	 	UMETA(DisplayName = "In Inventory"),
	ItemState_Used				UMETA(DisplayName = "Used"),
	ItemState_Custom		 	UMETA(DisplayName = "Custom"),
	ItemState_Invalid		 	UMETA(DisplayName = "Invalid"),
};