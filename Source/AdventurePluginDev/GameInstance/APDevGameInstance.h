// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AdventurePluginGameContext.h"
#include "APDevGameInstance.generated.h"

/**
 *
 */
UCLASS()
class ADVENTUREPLUGINDEV_API UAPDevGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
		UPROPERTY(Transient)
		UAdventurePluginGameContext* CurrentGameContext;




};
