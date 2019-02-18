#pragma once

#include "Core.h"
#include "Delegate.h"
#include "CombinableObject.h"
#include "CombinationInterface.h"
#include "AdventurePluginRuntime.h"
#include "UseActionType.h"
#include "CombinationWithSingleItemBase.h"
#include "GenericCombinationWithSingleItem.generated.h"

class UAdventurePluginGameContext;
/**
* Delegate to call when a combination is triggered.
* @param CombinationTarget The other item of this combination.
* @param GameContext Provides access to all Adventure Plugin data and functionality.
*/
DECLARE_DYNAMIC_DELEGATE_TwoParams(FCombinationEvent, UObject*, CombinationTarget, UAdventurePluginGameContext*, GameContext);
/**
* Represents a combination with a target object, with a specific constant name and an event to be executed when Execute is called.
*/
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UGenericCombinationWithSingleItem : public UCombinationWithSingleItemBase
{
	GENERATED_BODY()

public:
	/**
	* The event to be executed when Execute is called.
	*/
	UPROPERTY(BlueprintReadWrite)
	FCombinationEvent CombinationEvent;
	/**
	* Retrieves the debug name of this combination to be shown in editor. Contains identification of this class and Name. @see UGenericCombinationWithSingleItem#Name
	* @return The debug combination name.
	*/
	virtual FText GetDebugName_Implementation() override
	{
		return FText::Format(NSLOCTEXT("AP", "GenericCombinationWithSingleItemDebugName", "Generic combination with single item:{0}"), Name);
	}
	/**
	* Executes the action this combination represents, i.e. the CombinationEvent. @see UGenericCombinationWithSingleItem#CombinationEvent.
	* @param CombinationSource Ignored.
	* @param CombinationTarget The other object of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	virtual void Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override
	{
		CombinationEvent.Execute(CombinationTarget, GameContext);
	}
};