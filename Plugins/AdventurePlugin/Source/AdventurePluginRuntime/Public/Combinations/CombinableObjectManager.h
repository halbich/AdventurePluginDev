// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "Common/AdventurePluginGameContext.h"
#include "CombinableObject.h"
#include "CombinableObjectManager.generated.h"


/**
* A class that can manage instances of a combinable object.
* For each TSubclassOf<UCombinableObject> this class will return a single instance of that class, same across the entire game.
* Used because in editor we will work mainly with class definitions, whereas in game we will work mainly with class instances.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UCombinableObjectManager : public UObject
{
	GENERATED_BODY()

public:
	/**
	* Retrieves the single instance of the specified class, creating it if it is the first time this method was called with this parameter.
	* @param CombinableObjectClass The class whose instance is requested.
	* @return The only instance of the specified class.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Combinations")
	UCombinableObject* GetCombinableObjectInstance(TSubclassOf<UCombinableObject> CombinableObjectClass);
	/**
	* Removes all data from the manager. 
	* Used because the manager is not recreated upon PIE restart and it would happen that old classes, which should no longer exists, because of blueprint recompile, would stil be stored here.
	*/
	void ClearMap();


private:
	/**
	* Creates a new instance of the specified class and stores it in the map
	* Should only be called once for each CombinableObjectClass.
	*/
	void RegisterObject(TSubclassOf<UCombinableObject> CombinableObjectClass);
	/**
	* Stores all registered combinable objects.
	*/
	UPROPERTY(Transient)
	TMap<TSubclassOf<UCombinableObject>, UCombinableObject*> CombinableObjects;
};
