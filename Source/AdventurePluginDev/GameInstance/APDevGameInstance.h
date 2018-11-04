// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AdventurePluginGameContext.h"
#include "DialogueController.h"
#include "DialoguePresenterWidget.h"
#include "InventoryController.h"
#include "InventoryPresenterWidget.h"
#include "APDevGameInstance.generated.h"

/**
 *
 */
UCLASS()
class ADVENTUREPLUGINDEV_API UAPDevGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient, BlueprintReadOnly, Category="GameContext")
		UAdventurePluginGameContext* CurrentGameContext;

	virtual void Init() override;

	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable, Category = "Test")
		void TestContext();

private:
	void initCurrentGameContext();

};