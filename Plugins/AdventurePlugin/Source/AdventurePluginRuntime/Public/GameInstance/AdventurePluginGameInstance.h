// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Dialogue/Graph/DialogGraph.h"
#include "AdventurePluginGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	void ShowDialog(UDialogGraph* graph);
	
	
};
