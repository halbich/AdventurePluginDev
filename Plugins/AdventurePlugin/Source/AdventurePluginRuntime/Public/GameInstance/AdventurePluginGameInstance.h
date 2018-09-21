// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Dialogue/Graph/DialogGraph.h"
#include "Dialogue/Controller/DialogueController.h"
#include "Inventory/Manager/InventoryManager.h"
#include "Config/AdventurePluginConfig.h"
#include "AdventurePluginGameInstance.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	void ShowDialog(UDialogGraph* graph, UDialogueController* overrideController = nullptr);

	void ShowInventory(bool bShow);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	UInventoryManager* GetInventoryManager();

private:

	UPROPERTY(Transient)
		UDialogueController* defaultDialogueInstance;

	UPROPERTY(Transient)
		UDialogueController* currentDialogueInstance;

	UPROPERTY(Transient)
		UInventoryManager* inventoryManagerInstance;

	FORCEINLINE UDialogueController* getDefaultDialogueInstance()
	{
		if (defaultDialogueInstance && defaultDialogueInstance->IsValidLowLevel())
			return defaultDialogueInstance;

		auto settings = GetMutableDefault<UAdventurePluginConfig>();

		if (settings->DefaultDialogueController.IsValid()) {
			// we have C++ class
			auto inst = settings->DefaultDialogueController.Get();
			if (inst)
				defaultDialogueInstance = inst->GetDefaultObject<UDialogueController>();
		}
		else
		{
			// we have Blueprint class
			auto inst = settings->DefaultDialogueController.LoadSynchronous();
			if (inst)
				defaultDialogueInstance = inst->GetDefaultObject<UDialogueController>();
		}

		return defaultDialogueInstance;
	}

	FORCEINLINE void ensureInventoryManagerInstance()
	{
		if (inventoryManagerInstance && inventoryManagerInstance->IsValidLowLevel()) return;
		auto settings = GetMutableDefault<UAdventurePluginConfig>();
		auto inst = (settings->DefaultInventoryManager.IsValid())
			? settings->DefaultInventoryManager.Get()				// we have C++ class
			: settings->DefaultInventoryManager.LoadSynchronous();	// we have Blueprint class
		if (inst)
		{
			inventoryManagerInstance = inst->GetDefaultObject<UInventoryManager>();
			inventoryManagerInstance->SetGameInstance(this);
		}
		// TODO else report biiig error
	}
};
