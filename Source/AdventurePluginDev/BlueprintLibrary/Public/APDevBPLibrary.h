// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "AdventurePluginGameContext.h"
#include "GameInstance/APDevGameInstance.h"
#include "APDevBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREPLUGINDEV_API UAPDevBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "APDevBPLibrary", meta = (WorldContext = worldObjectContext))
		static UAdventurePluginGameContext* GetCurrentGameContext(UObject* worldObjectContext);
	
};
