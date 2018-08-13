// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AdventurePluginConfig.generated.h"

/**
 * 
 */
UCLASS(config = AdventurePlugin, defaultconfig)
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginConfig : public UObject
{
	GENERATED_UCLASS_BODY()

	/** Sample bool property */ 
	UPROPERTY(EditAnywhere, config, Category = Custom) 
	bool bSampleBool;

	/** Sample float property that requires a restart */ 
	UPROPERTY(EditAnywhere, config, Category = Custom, meta = (ConfigRestartRequired = true))
	float SampleFloatRequireRestart;

	/** Sample string list */ 
	UPROPERTY(config, EditAnywhere, Category = Custom)
	TArray<FString> SampleStringList;

	/** Or add min, max or clamp values to the settings */ 
	UPROPERTY(config, EditAnywhere, Category = Custom, meta = (UIMin = 1, ClampMin = 1))
	int32 ClampedIntSetting;

	/** We can even use asset references */ 
	UPROPERTY(config, EditAnywhere, Category = Materials, meta = (AllowedClasses = "MaterialInterface"))
	FStringAssetReference StringMaterialAssetReference;
	
	
};
