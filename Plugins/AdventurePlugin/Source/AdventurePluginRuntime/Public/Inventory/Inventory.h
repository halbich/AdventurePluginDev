#pragma once

#include "Core.h"
#include "Inventory/InventoryItem.h"
#include "Inventory.generated.h"

UCLASS()
class ADVENTUREPLUGINRUNTIME_API UInventory : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<UInventoryItem*> Items;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(UInventoryItem* item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UInventoryItem* item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(UInventoryItem* item);
};