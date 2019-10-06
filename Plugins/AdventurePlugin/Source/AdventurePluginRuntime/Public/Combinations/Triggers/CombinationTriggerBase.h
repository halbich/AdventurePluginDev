#pragma once

#include "CoreMinimal.h"
#include "WorldContextProvidingObject.h"
#include "CombinationTriggerBase.generated.h"

class UAdventurePluginGameContext;

/**
* A class representing a possible trigger for a combination, like combining with a specific item, combining with items with some tags, combining just with some specific subclasses etc.
*/
UCLASS(Abstract, BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UCombinationTriggerBase : public UWorldContextProvidingObject
{
	GENERATED_BODY()

public:

	UCombinationTriggerBase(): Super() { }
	UCombinationTriggerBase(int Priority): Super(), Priority(Priority) { }

	/**
	* When multiple combinations have valid triggers, only the one with the highest priority is executed.
	* The possible values for this variable must be agreed upon.
	* For example, in our example project, 1000 is for single target combinations, 500 is for multitarget and 0 is for fallbacks.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Adventure Plugin")
	int Priority;

	/**
	* Retrieves the list of all possible target classes. Target classes are those for which CanCombineWith can return true.
	* @see UCombination#CanCombineWith
	* @return The list of all possible target classes.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations")
	TArray<UClass*> GetCombinationTargetClasses();

	/**
	* Checks whether it is possible to combine the specified items.
	* @param CombinationSource The object on which the combination is defined.
	* @param CombinationTarget The other object of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if the combination is possible, otherwise false
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations", meta = (AdvancedDisplay = GameContextOverride))
	bool CanCombineWith(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride);

};