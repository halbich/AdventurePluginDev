// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Combinations/CombinableObjectManager.h"
#include "AdventureCharacter.h"
#include "AdventureCharacterManager.generated.h"

/**
* Each UAdventureCharacter class should have only one instance common across the entire game.
* This class creates those single instances and returns them when requested.
* @see UAdventureCharacter
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UAdventureCharacterManager : public UCombinableObjectManager
{
	GENERATED_BODY()

public:
	/**
	* Retrieves the instance of the specified adventure character class.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Character")
		UAdventureCharacter* GetCharacter(TSubclassOf<UAdventureCharacter> Character)
	{
		return Cast<UAdventureCharacter>(GetCombinableObjectInstance(Character));
	}
};
