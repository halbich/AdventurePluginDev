#include "Core.h"
#include "LocalCombinationInfo.generated.h"

#pragma once

USTRUCT(BlueprintType)
struct FLocalCombinationInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
		FText Name;

	UPROPERTY(VisibleAnywhere)
		TArray<UBlueprint*> TargetBlueprints;

	UPROPERTY(VisibleAnywhere)
		TArray<UClass*> TargetClasses;

};
