// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UniquePtr.h"
#include "Inventory/Inventory.h"
#include "InventoryPresenterInterface.generated.h"

class UInventoryController;

/**
 *
 */
UINTERFACE(BlueprintType)
class ADVENTUREPLUGINRUNTIME_API UInventoryPresenterInterface : public UInterface
{
	GENERATED_BODY()


};

class ADVENTUREPLUGINRUNTIME_API IInventoryPresenterInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Inventory")
		void ShowInventory(UInventory* Inventory, UInventoryController* InventoryController);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Inventory")
		void HideInventory(UInventoryController* InventoryController);
};
