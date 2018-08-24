// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameStateMonitor/AdventurePluginGameInstance.h"
#include "DialogGraph/DialogGraph.h"
#include "AdventurePluginBlueprintLibrary.generated.h"


#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,5, FColor::White,text)
#define printR(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,5, FColor::Red,text)

/**
 *
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "AdventurePluginBPLibrary", meta = (WorldContext = "WorldContextObject"))
		static void ShowDialog(UObject* WorldContextObject, UDialogGraph* graph);

};
