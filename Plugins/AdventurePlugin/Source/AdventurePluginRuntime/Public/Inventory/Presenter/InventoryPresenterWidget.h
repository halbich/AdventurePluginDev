// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPresenterInterface.h"
#include "InventoryPresenterWidget.generated.h"


DECLARE_DYNAMIC_DELEGATE(FUniversalConsoleEvent);

/**
 *
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UInventoryPresenterWidget : public UUserWidget, public IInventoryPresenterInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = output)
		TArray<FUniversalConsoleEvent> actions;

	void ShowInventory(UInventory* inventory, UInventoryController* manager);

	void HideInventory(UInventoryController* controller);
};
