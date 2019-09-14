#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Combinations/CombinableObject.h"
#include "Combinations/CombinationInterface.h"
#include "AdventurePluginRuntime.h"
#include "Inventory/Structs/UseActionType.h"
#include "CombinationWithSingleItemBase.generated.h"

class UAdventurePluginGameContext;

/**
* Abstract class representing a combination with a target object, with a specific constant name. 
* The combination action must be specified in subclasses.
*/
UCLASS(Abstract, BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UCombinationWithSingleItemBase : public UObject, public ICombinationInterface
{
	GENERATED_BODY()

public:

	/**
	* The name of this combination.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Adventure Plugin")
	FText Name;

	/**
	* The type of action of this combination.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Adventure Plugin")
	FUseActionType ActionType;

	/**
	* The single target class of this combination.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Adventure Plugin")
	TSubclassOf<UCombinableObject> TargetClass;

	/**
	* Retrieves the name of this combination that can be displayed to the user. Constant, getter for UCombinationWithSingleItemBase#Name.
	* @param CombinationSource The object where this combination originated.
	* @param CombinationTarget The target of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The name of the combination.
	*/
	virtual FText GetName_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override
	{
		return Name;
	}

	/**
	* Retrieves the debug name of this combination to be shown in editor. Must be overriden.
	* @return The debug combination name.
	*/
	virtual FText GetDebugName_Implementation() override
	{
		check (false && "This method should be overriden");
		return FText::Format(NSLOCTEXT("AdventurePlugin", "CombinationWithSingleItemDebugName", "Abstract combination with single item:{0}"), Name);
	}

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
	virtual	bool CanCombineWith_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(CombinationTarget))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "CombinationWithSingleItemBase_CanCombineWith_NullItem", "CombinationWithSingleItemBase:CanCombineWith::The other item is null or invalid."));
			return false;
		}
		return CombinationTarget->GetClass()->IsChildOf(TargetClass);
	}

	/**
	* Executes the action this combination represents. Must be overriden.
	* @param CombinationSource The object that started the execution.
	* @param CombinationTarget The other object of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	virtual void Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override
	{
		check(false && "Must be overriden.");
	}

	/**
	* Retrieves the type of this combination that can be displayed to the user. Constant, getter for UCombinationWithSingleItemBase#ActionType.
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