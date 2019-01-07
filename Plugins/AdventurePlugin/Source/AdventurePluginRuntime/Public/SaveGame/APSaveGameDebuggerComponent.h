// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AdventurePluginSaveGame.h"
#include "APSaveGameDebuggerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVENTUREPLUGINRUNTIME_API UAPSaveGameDebuggerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAPSaveGameDebuggerComponent();

	UPROPERTY(EditAnywhere, Instanced, Category = "Save Game")
		UAdventurePluginSaveGame* DebugSaveGame;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
