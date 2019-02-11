// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Combinations/CombinableObjectManager.h"
#include "AdventureCharacter.h"
#include "AdventureCharacterManager.generated.h"

/**
*
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UAdventureCharacterManager : public UCombinableObjectManager
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Character")
		UAdventureCharacter* GetCharacter(TSubclassOf<UAdventureCharacter> Character)
	{
		return Cast<UAdventureCharacter>(GetCombinableObjectInstance(Character));
	}
};
