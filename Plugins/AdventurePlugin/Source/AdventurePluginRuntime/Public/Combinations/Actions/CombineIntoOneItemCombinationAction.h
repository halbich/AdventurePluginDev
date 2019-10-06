#pragma once

#include "CoreMinimal.h"
#include "Combinations/Actions/CombinationActionBase.h"
#include "Inventory/InventoryItem.h"
#include "CombineIntoOneItemCombinationAction.generated.h"

class UAdventurePluginGameContext;

/**
* A class representing a possible trigger for a combination, like combining with a specific item, combining with items with some tags, combining just with some specific subclasses etc.
*/
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UCombineIntoOneItemCombinationAction : public UCombinationActionBase
{
	GENERATED_BODY()

public:

	/**
	* The class specifying the item to be added when this combination is triggered.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Adventure Plugin")
		TSubclassOf<UInventoryItem> ResultItemClass;
	/**
	* Executes the action this combination represents.
	* @param CombinationSource The object on which the combination is defined.
	* @param CombinationTarget The other object of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	virtual void Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride) override;

};