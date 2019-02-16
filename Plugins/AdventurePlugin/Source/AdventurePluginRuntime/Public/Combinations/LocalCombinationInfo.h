#include "Core.h"
#include "LocalCombinationInfo.generated.h"

#pragma once
/**
* Information about a combination defined on an CombinableObject. This should be used only in editor time to describe combinations defined on an object.
*/
USTRUCT(BlueprintType)
struct FLocalCombinationInfo
{
	GENERATED_BODY()
	/**
	* The debug name of the combination.
	*/
	UPROPERTY(VisibleAnywhere)
	FText Name;
	/**
	* All blueprints which specify target classes of the combination. Together with TargetClasses specifies all targets of this combination.
	*/
	UPROPERTY(VisibleAnywhere)
	TArray<UBlueprint*> TargetBlueprints;
	/**
	* Native classes which specify target classes of the combination. Together with TargetBlueprints specifies all targets of this combination
	*/
	UPROPERTY(VisibleAnywhere)
	TArray<UClass*> TargetClasses;

};
