// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AdventurePluginGameContext.h"
#include "DialogController.h"
#include "DialogPresenterWidget.h"
#include "InventoryController.h"
#include "InventoryPresenterWidget.h"
#include "AdventurePluginSaveGame.h"
#include "ItemManager.h"
#include "AdventureCharacterManager.h"
#include "AdventurePluginGameInstance.generated.h"

/**
 * A game instance that can be used for projects using our plugin.
 * It contains a single game context that contains instances of the classes specified in the project configuration.
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	/**
	* The game context used by this game instance.
	*/
	UPROPERTY(Transient, BlueprintReadOnly, Category="GameContext")
		UAdventurePluginGameContext* CurrentGameContext;

	virtual void Init() override;

	virtual void Shutdown() override;

private:
	/**
	* Initializes the game context based on the project configuration.
	*/
	void InitCurrentGameContext();

};
