// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "ItemCombinationInterface.generated.h"

class UAdventurePluginGameContext;

/**
*
*/
UINTERFACE(BlueprintType)
class ADVENTUREPLUGINRUNTIME_API UItemCombinationInterface : public UInterface
{
	GENERATED_BODY()


};

class ADVENTUREPLUGINRUNTIME_API IItemCombinationInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
		FText GetName();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
		TArray<UClass*> GetCombinationTargetClasses();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
		bool CanCombineWith(UObject* CombinationTarget);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
		void Execute(UObject* CombinationTarget, UAdventurePluginGameContext* GameContext);
};
