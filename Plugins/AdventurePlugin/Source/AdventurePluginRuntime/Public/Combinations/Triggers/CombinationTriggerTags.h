#pragma once

#include "CoreMinimal.h"
#include "WorldContextProvidingObject.h"
#include "CombinationTriggerBase.h"
#include "AdventurePluginRuntime.h"
#include "GameplayTags.h"
#include "CombinableObject.h"
#include "CombinationTriggerTags.generated.h"

class UAdventurePluginGameContext;

/**
* A class representing a possible trigger for a combination when combining it with objects of specific class.
*/
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UCombinationTriggerTags : public UCombinationTriggerBase
{
	GENERATED_BODY()

public:
	// Set the default priority to 1000
	UCombinationTriggerTags() : Super(10) { }
	/**
	* The single target class of this combination.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adventure Plugin")
	FGameplayTagContainer RequiredTags;

	/**
	* Retrieves the list of all possible target classes. Constant, getter for UCombinationWithSingleItemBase#TargetClass wrapped in an array.
	* TODO: Does not work, implement or get rid of this method.
	* @return The list of all possible target classes.
	*/
	virtual TArray<UClass*> GetCombinationTargetClasses_Implementation() override
	{
		TArray<UClass*> ToReturn = TArray<UClass*>();
		return ToReturn;
	}

	/**
	* Checks whether it is possible to combine the specified items.
	* @param CombinationSource Ignored.
	* @param CombinationTarget The other object of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if the combination is possible, i.e. CombinationTarget inherits from UCombinationWithSingleItemBase#TargetClass otherwise false.
	*/
	virtual	bool CanCombineWith_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride) override
	{
		if (!IsValid(CombinationTarget))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "CombinationWithSingleItemBase_CanCombineWith_NullItem", "CombinationWithSingleItemBase:CanCombineWith::The other item is null or invalid."));
			return false;
		}
		auto* CombinationTargetCasted = Cast<UCombinableObject>(CombinationTarget);
		if (!IsValid(CombinationTargetCasted))
		{
			return false;
		}
		return CombinationTargetCasted->ObjectTags.HasAll(RequiredTags);
	}
};