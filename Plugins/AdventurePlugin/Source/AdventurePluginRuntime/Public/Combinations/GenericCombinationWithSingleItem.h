#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Common/AdventurePluginGameContext.h"
#include "Combinations/CombinableObject.h"
#include "AdventurePluginRuntime.h"
#include "Inventory/Structs/UseActionType.h"
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
	UPROPERTY(BlueprintReadWrite, Category = "Adventure Plugin")
	FCombinationEvent CombinationEvent;

	/**
	* Retrieves the debug name of this combination to be shown in editor.
	* Contains identification of this class and UGenericCombinationWithSingleItem#Name.
	* @return The debug combination name.
	*/
	virtual FText GetDebugName_Implementation() override
	{
		return FText::Format(NSLOCTEXT("AdventurePlugin", "GenericCombinationWithSingleItemDebugName", "Generic combination with single item:{0}"), Name);
	}

	/**
	* Executes the action this combination represents, the UGenericCombinationWithSingleItem#CombinationEvent.
	* @param CombinationSource Ignored.
	* @param CombinationTarget The other object of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	virtual void Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride) override
	{
		auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
		CombinationEvent.Execute(CombinationTarget, GameContext);
	}
};