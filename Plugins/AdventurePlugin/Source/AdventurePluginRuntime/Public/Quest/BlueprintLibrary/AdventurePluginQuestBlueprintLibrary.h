// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuestGraphBool.h"
#include "QuestGraphFlag.h"
#include "QuestGraphEvent.h"
#include "QuestGraphInteger.h"
#include "QuestGraphString.h"
#include "AdventurePluginQuestBlueprintLibrary.generated.h"

/**
* This library defines static functions regarding quests.
*/
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginQuestBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Quest")
		static bool GetQuestBool(UAdventurePluginGameContext* GameContext, FQuestGraphBool QuestBoolVariable);
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest")
		static void SetQuestBool(UAdventurePluginGameContext* GameContext, FQuestGraphBool QuestBoolVariable, bool bNewValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Quest")
		static bool GetQuestFlag(UAdventurePluginGameContext* GameContext, FQuestGraphFlag QuestFlag);
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest")
		static void SetQuestFlag(UAdventurePluginGameContext* GameContext, FQuestGraphFlag QuestFlag);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Quest")
		static int32 GetQuestInteger(UAdventurePluginGameContext* GameContext, FQuestGraphInteger QuestIntegerVariable);
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest")
		static void SetQuestInteger(UAdventurePluginGameContext* GameContext, FQuestGraphInteger QuestIntegerVariable, int32 NewValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Quest")
		static FString GetQuestString(UAdventurePluginGameContext* GameContext, FQuestGraphString QuestStringVariable);
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest")
		static void SetQuestString(UAdventurePluginGameContext* GameContext, FQuestGraphString QuestStringVariable, const FString& NewValue);

	UFUNCTION(BlueprintCallable, Category = "AdventurePluginBPLibrary|Quest")
		static bool BindQuestEvent(UAdventurePluginGameContext* GameContext, FQuestGraphEvent QuestEvent, FQuestEvent QuestEventHandler);
private:
};
