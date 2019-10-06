#pragma once

#include "CoreMinimal.h"
#include "WorldContextProvidingObject.h"
#include "CombinationTriggerBase.h"
#include "AdventurePluginRuntime.h"
#include "CombinationTriggerAll.generated.h"

class UAdventurePluginGameContext;
class UCombinableObject;

/**
* A class representing a possible trigger that will always be true, valid for combinations with any object.
*/
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UCombinationTriggerAll : public UCombinationTriggerBase
{
	GENERATED_BODY()

public:
	// Set the default priority to 1000
	UCombinationTriggerAll() : Super(10) { }
	/**
	* The single target class of this combination.

	/**
	* This should return all possible classes, but as it is used only in development and we want to save space, let's just return nothing
	* TODO: Wouldn't it make sense to remove this method alltogether?
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
		return true;
	}
};