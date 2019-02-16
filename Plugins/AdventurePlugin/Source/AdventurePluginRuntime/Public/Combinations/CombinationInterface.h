// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "UseActionType.h"
#include "CombinationInterface.generated.h"

class UAdventurePluginGameContext;
/**
*A class implementing this interface represents a combination, i.e. that some object can be combined with another object and that combination will cause something will happen.
*/
UINTERFACE(BlueprintType)
class ADVENTUREPLUGINRUNTIME_API UCombinationInterface : public UInterface
{
	GENERATED_BODY()


};

class ADVENTUREPLUGINRUNTIME_API ICombinationInterface
{
	GENERATED_BODY()

public:
	/*The name of this combination. It should be possible to display this name to the user.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations")
	FText GetName();
	/*The debug name of this combination to be shown in editor. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations")
	FText GetDebugName();
	/*Retrieves the list of all target classes. Target classes are those for whose instances CanCombineWith will return true.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations")
	TArray<UClass*> GetCombinationTargetClasses();
	/*Returns true if this is a combination with the specified object.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations")
	bool CanCombineWith(UObject* CombinationSource, UObject* CombinationTarget);
	/*Called when the user triggers this combination.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations")
	void Execute(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext);
	/*Returns the type of this combination when applying this combination for these two specific objects.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations")
	FUseActionType GetUseActionType(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext);
};
