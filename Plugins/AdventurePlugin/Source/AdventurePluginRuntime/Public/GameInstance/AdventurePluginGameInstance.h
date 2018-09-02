// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Dialogue/Graph/DialogGraph.h"
#include "Dialogue/Controller/DialogueController.h"
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

private:

	UPROPERTY(Transient)
		UDialogueController* defaultDialogueInstance;

	UPROPERTY(Transient)
		UDialogueController* currentDialogueInstance;

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
};
