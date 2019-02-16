// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AdventurePluginRuntime.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogController.h"
#include "Quest/Graph/QuestGraph.h"
#include "Dialog/Graph/DialogGraph.h"
#include "Dialog/Graph/DialogGraphNode.h"
#include "Dialog/Structs/DialogGraphEntryPoint.h"
#include "InventoryController.h"
#include "AdventurePluginRuntime.h"
#include "AdventureCharacter.h"
#include "AdventurePluginBlueprintLibrary.generated.h"


/**
 *
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Dialog")
		static void ShowDialogFromEntryPoint(UAdventurePluginGameContext* GameContext, FDialogGraphEntryPoint EntryPoint);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Dialog")
		static void ShowDialog(UAdventurePluginGameContext* GameContext, UDialogGraph* DialogGraph);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Inventory")
		static void ShowInventory(UAdventurePluginGameContext* GameContext, bool bShow);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Inventory")
		static UInventoryItem* GetItem(UAdventurePluginGameContext* GameContext, TSubclassOf<UInventoryItem> Item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Character")
		static UAdventureCharacter* GetAdventureCharacter(UAdventurePluginGameContext* GameContext, TSubclassOf<UAdventureCharacter> Character);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin", meta = (WorldContext = WorldObjectContext))
		static UAdventurePluginGameContext* GetCurrentGameContext(UObject* WorldObjectContext);

private:
};
