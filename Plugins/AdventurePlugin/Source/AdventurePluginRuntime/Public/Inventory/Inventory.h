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

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
	bool HasItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContext);

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
	bool AddItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContext);

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
	bool RemoveItem(UInventoryItem* Item, UAdventurePluginGameContext* GameContext);
	// Call if adding or removing multiple items in a row and you want to fire only one update event for all of those updates.
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
	void BeginUpdate();
	// Call if adding or removing multiple items in a row and you want to fire only one update event for all of those updates.
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Inventory")
	void EndUpdate();
private:
	UPROPERTY(Transient)
	bool bIsUpdating;
};