#pragma once

#include "CoreMinimal.h"
#include "WorldContextProvidingObject.h"
#include "CombinationTriggerBase.h"
#include "AdventurePluginRuntime.h"
#include "SingleObjectCombinationTrigger.generated.h"

class UAdventurePluginGameContext;
class UCombinableObject;

/**
* A class representing a possible trigger for a combination, like combining with a specific item, combining with items with some tags, combining just with some specific subclasses etc.
*/
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API USingleObjectCombinationTrigger : public UCombinationTriggerBase
{
	GENERATED_BODY()

public:
	// Set the default priority to 1000
	USingleObjectCombinationTrigger(): Super(1000) { }
	/**
	* The single target class of this combination.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Adventure Plugin")
	TSubclassOf<UCombinableObject> TargetClass;

	/**
	* Retrieves the list of all possible target classes. Constant, getter for UCombinationWithSingleItemBase#TargetClass wrapped in an array.
	* @return The list of all possible target classes.
	*/
	virtual TArray<UClass*> GetCombinationTargetClasses_Implementation() override
	{
		TArray<UClass*> ToReturn = TArray<UClass*>();
		ToReturn.Add(TargetClass);
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
		return CombinationTarget->GetClass()->IsChildOf(TargetClass);
	}
};