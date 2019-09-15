#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "Combinations/CombinableObjectManager.h"
#include "InventoryItem.h"
#include "ItemManager.generated.h"

/**
* This class is responsible for retrieving item instances for UInventoryItem classes.
* There should always be only one instance of one item class, this manager is where that instance is stored and retrieved from.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UItemManager : public UCombinableObjectManager
{
	GENERATED_BODY()

public:

	/**
	* Retrieves an instance of the specified item class
	* @param Item The item whose instance is requested.
	* @return The instance of that item.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
	UInventoryItem* GetItem(TSubclassOf<UInventoryItem> Item)
	{
		return Cast<UInventoryItem>(GetCombinableObjectInstance(Item));
	}
};
