// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "Common/AdventurePluginGameContext.h"
#include "CombinableObject.h"
#include "CombinableObjectManager.generated.h"


/**
*
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UCombinableObjectManager : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Combinations")
		UCombinableObject* GetCombinableObjectInstance(TSubclassOf<UCombinableObject> CombinableObjectClass);

	void ClearMap();


private:

	void RegisterObject(TSubclassOf<UCombinableObject> CombinableObjectClass);

	UPROPERTY(Transient)
		TMap<TSubclassOf<UCombinableObject>, UCombinableObject*> CombinableObjects;
};
