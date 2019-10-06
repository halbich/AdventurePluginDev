#pragma once

#include "CoreMinimal.h"
#include "Combinations/Actions/CombinationActionBase.h"
#include "Delegates/Delegate.h"
#include "GenericCombinationAction.generated.h"

class UAdventurePluginGameContext;

/**
* Delegate to call when a combination is triggered.
* @param CombinationTarget The other item of this combination.
* @param GameContext Provides access to all Adventure Plugin data and functionality.
*/
DECLARE_DYNAMIC_DELEGATE_TwoParams(FCombinationEvent, UObject*, CombinationTarget, UAdventurePluginGameContext*, GameContext);

/**
* A class representing a possible trigger for a combination, like combining with a specific item, combining with items with some tags, combining just with some specific subclasses etc.
*/
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UGenericCombinationAction : public UCombinationActionBase
{
	GENERATED_BODY()

public:

	/**
	* The event to be executed when Execute is called.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Adventure Plugin")
	FCombinationEvent CombinationEvent;
	/**
	* Executes the action this combination represents.
	* @param CombinationSource The object on which the combination is defined.
	* @param CombinationTarget The other object of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	virtual void Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride) override;

};