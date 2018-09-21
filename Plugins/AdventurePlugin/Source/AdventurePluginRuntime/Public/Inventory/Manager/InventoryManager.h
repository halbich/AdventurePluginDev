// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "Inventory/Presenter/InventoryPresenterWidget.h"
#include "Config/AdventurePluginConfig.h"
#include "Kismet/GameplayStatics.h"
#include "InventoryManager.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UInventoryManager : public UObject
{
	GENERATED_BODY()

public:

	UInventoryManager()
	{
		defaultInventory = NewObject<UInventory>();
	}

	void ShowInventory(UInventory* inventory = nullptr);

	void HideInventory();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	UInventory* GetInventory(FName name);

	void SetGameInstance(UGameInstance* instance);

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UInventoryPresenterWidget> DefaultPresenter;

private:

	UPROPERTY(Transient)
	UInventory* defaultInventory;

	UPROPERTY(Transient)
	UInventoryPresenterWidget* presenterInstance;

	UPROPERTY(Transient)
	UGameInstance* cachedGameInstance;

	FORCEINLINE void ensurePresenterInstance()
	{
		check(cachedGameInstance && cachedGameInstance->IsValidLowLevel());
		if (presenterInstance && presenterInstance->IsValidLowLevel()) return;
		auto cdo = DefaultPresenter.Get();
		if (cdo) presenterInstance = CreateWidget<UInventoryPresenterWidget>(cachedGameInstance, cdo);
		if (presenterInstance && presenterInstance->IsValidLowLevel()) return;
		auto settings = GetMutableDefault<UAdventurePluginConfig>();
		auto inst = (settings->DefaultInventoryPresenterWidget.IsValid())
			? settings->DefaultInventoryPresenterWidget.Get()				// we have C++ class
			: settings->DefaultInventoryPresenterWidget.LoadSynchronous();	// we have Blueprint class
		if (inst) presenterInstance = CreateWidget<UInventoryPresenterWidget>(cachedGameInstance, inst);
		// TODO else report biiig error
	}
};
