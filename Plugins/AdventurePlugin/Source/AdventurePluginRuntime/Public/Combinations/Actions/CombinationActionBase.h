#pragma once

#include "CoreMinimal.h"
#include "WorldContextProvidingObject.h"
#include "CombinationActionBase.generated.h"

class UAdventurePluginGameContext;

/**
* A class representing a possible trigger for a combination, like combining with a specific item, combining with items with some tags, combining just with some specific subclasses etc.
*/
UCLASS(Abstract, BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UCombinationActionBase : public UWorldContextProvidingObject
{
	GENERATED_BODY()

public:

	/**
	* Executes the action this combination represents.
	* @param CombinationSource The object on which the combination is defined.
	* @param CombinationTarget The other object of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations", meta = (AdvancedDisplay = GameContextOverride))
	void Execute(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride);

};