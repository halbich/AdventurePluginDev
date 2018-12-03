#pragma once

#include "Core.h"
#include "Inventory/InventoryItem.h"
#include "Inventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryChangedEvent, UInventoryItem*, ChangedItem);

UCLASS()
class ADVENTUREPLUGINRUNTIME_API UInventory : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<UInventoryItem*> Items;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FInventoryChangedEvent InventoryChanged;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(UInventoryItem* item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UInventoryItem* item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(UInventoryItem* item);
	// Call if adding or removing multiple items in a row and you want to fire only one update event for all of those updates.
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void BeginUpdate();
	// Call if adding or removing multiple items in a row and you want to fire only one update event for all of those updates.
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void EndUpdate();
private:
	UPROPERTY(Transient)
	bool isUpdating;
};