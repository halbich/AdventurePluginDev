// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogueController.h"
#include "Dialogue/Graph/DialogGraph.h"
#include "Dialogue/Graph/DialogGraphNode.h"
#include "InventoryController.h"
#include "AdventurePluginRuntime.h"
#include "AdventurePluginBlueprintLibrary.generated.h"


/**
 *
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "AdventurePluginBPLibrary")
		static void ShowDialogFromEntryPoint(UAdventurePluginGameContext* gameContext, UDialogGraph* graph, UDialogGraphNode* startNode);

	UFUNCTION(BlueprintCallable, Category = "AdventurePluginBPLibrary")
		static void ShowDialog(UAdventurePluginGameContext* gameContext, UDialogGraph* graph);

	UFUNCTION(BlueprintCallable, Category = "AdventurePluginBPLibrary")
		static void ShowInventory(UAdventurePluginGameContext* gameContext, bool bShow);

private:
};
