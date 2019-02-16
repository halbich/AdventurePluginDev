#pragma once

#include "Core.h"
#include "Delegate.h"
#include "InventoryItem.h"
#include "CombinationInterface.h"
#include "UseActionType.h"
#include "SimpleCombinationWithSingleItem.generated.h"

class UAdventurePluginGameContext;

/**
* Represents a combination with a target object and with a specific constant name.
* When the combination is triggered, both combined items will be removed from inventory and a new specified item will be added.
*/
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API USimpleCombinationWithSingleItem : public UObject, public ICombinationInterface
{
	GENERATED_BODY()

public:
	/**
	* The name of this combination.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;
	/**
	* The type of action of this combination.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FUseActionType ActionType;
	/** 
	* The class specifying the item to be added when this combination is triggered.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UInventoryItem> ResultItemClass;
	/**
	* The single target class of this combination.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCombinableObject> TargetClass;
	/**
	* Retrieves the name of this combination that can be displayed to the user. Constant, getter for Name. @see USimpleCombinationWithSingleItem#Name
	* @param CombinationSource Ignored.
	* @param CombinationTarget Ignored.
	* @param GameContext Ignored
	* @return The name of the combination.
	*/
	virtual FText GetName_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override
	{
		return Name;
	}
	/**
	* Retrieves the debug name of this combination to be shown in editor. Contains identification of this class and Name. @see USimpleCombinationWithSingleItem#Name
	* @return The debug combination name.
	*/
	virtual FText GetDebugName_Implementation() override
	{
		return FText::Format(NSLOCTEXT("AP", "SimpleCombinationWithSingleItemDebugName", "Simple combination with single item:{0}"), Name);
	}
	/**
	* Retrieves the list of all possible target classes. Constant, getter for TargetClass wrapped in an array. @see USimpleCombinationWithSingleItem#TargetClass
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
	* @param GameContext Ignored.
	* @return True if the combination is possible, i.e. CombinationTarget inherits from TargetClass otherwise false. @see USimpleCombinationWithSingleItem#TargetClass.
	*/
	virtual	bool CanCombineWith_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override;
	/**
	* Executes the action this combination represents.
	* Removes both combined items from the inventory and adds an instance of ResultItemClass to the inventory. See USimpleCombinationWithSingleItem#ResultItemClass.
	* @param CombinationSource The source object of the combination.
	* @param CombinationTarget The other object of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	virtual void Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override;
	/**
	* Retrieves the type of this combination that can be displayed to the user. Constant, getter for ActionType. @see USimpleCombinationWithSingleItem#ActionType
	* @param CombinationSource Ignored.
	* @param CombinationTarget Ignored.
	* @param GameContext Ignored
	* @return The type of the combination.
	*/
	FUseActionType GetUseActionType_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override
	{
		return ActionType;
	}
};