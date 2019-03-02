#pragma once

#include "Core.h"
#include "Delegate.h"
#include "InventoryItem.h"
#include "CombinationInterface.h"
#include "UseActionType.h"
#include "CombinationWithSingleItemBase.h"
#include "SimpleCombinationWithSingleItem.generated.h"

class UAdventurePluginGameContext;

/**
* Represents a combination with a target object and with a specific constant name.
* When the combination is triggered, both combined items will be removed from inventory and a new specified item will be added.
*/
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API USimpleCombinationWithSingleItem : public UCombinationWithSingleItemBase
{
	GENERATED_BODY()

public:

	/** 
	* The class specifying the item to be added when this combination is triggered.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UInventoryItem> ResultItemClass;

	/**
	* Retrieves the debug name of this combination to be shown in editor. Contains identification of this class and Name. @see USimpleCombinationWithSingleItem#Name
	* @return The debug combination name.
	*/
	virtual FText GetDebugName_Implementation() override
	{
		return FText::Format(NSLOCTEXT("AdventurePlugin", "SimpleCombinationWithSingleItemDebugName", "Simple combination with single item:{0}"), Name);
	}

	/**
	* Executes the action this combination represents.
	* Removes both combined items from the inventory and adds an instance of ResultItemClass to the inventory. See USimpleCombinationWithSingleItem#ResultItemClass.
	* @param CombinationSource The source object of the combination.
	* @param CombinationTarget The other object of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	virtual void Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override;
};