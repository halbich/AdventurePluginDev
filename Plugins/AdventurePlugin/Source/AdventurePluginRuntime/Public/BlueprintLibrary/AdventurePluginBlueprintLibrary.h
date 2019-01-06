// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AdventurePluginRuntime.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogueController.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "Dialogue/Graph/DialogGraph.h"
#include "Dialogue/Graph/DialogGraphNode.h"
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

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		static void ShowDialogFromEntryPoint(UAdventurePluginGameContext* gameContext, UDialogGraph* graph, UDialogGraphNode* startNode);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		static void ShowDialog(UAdventurePluginGameContext* gameContext, UDialogGraph* graph);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		static void ShowInventory(UAdventurePluginGameContext* gameContext, bool bShow);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin")
		static UInventoryItem* GetItem(UAdventurePluginGameContext* gameContext, TSubclassOf<UInventoryItem> Item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin")
		static UAdventureCharacter* GetAdventureCharacter(UAdventurePluginGameContext* gameContext, TSubclassOf<UAdventureCharacter> Character);

	UFUNCTION(BlueprintCallable, Category = "AdventurePluginBPLibrary")
		static bool BindQuestEvent(UAdventurePluginGameContext* gameContext, UQuestGraph* graph, FName eventName, FQuestEvent questEvent);

private:
};
