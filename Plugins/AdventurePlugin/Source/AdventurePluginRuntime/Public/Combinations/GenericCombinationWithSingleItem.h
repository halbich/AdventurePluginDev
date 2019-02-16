#pragma once

#include "Core.h"
#include "Delegate.h"
#include "CombinableObject.h"
#include "CombinationInterface.h"
#include "AdventurePluginRuntime.h"
#include "UseActionType.h"
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
class ADVENTUREPLUGINRUNTIME_API UGenericCombinationWithSingleItem : public UObject, public ICombinationInterface
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
	* The event to be executed when Execute is called.
	*/
	UPROPERTY(BlueprintReadWrite)
	FCombinationEvent CombinationEvent;
	/**
	* The single target class of this combination.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCombinableObject> TargetClass;
	/**
	* Retrieves the name of this combination that can be displayed to the user. Constant, getter for Name. @see UGenericCombinationWithSingleItem#Name
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
	* Retrieves the debug name of this combination to be shown in editor. Contains identification of this class and Name. @see UGenericCombinationWithSingleItem#Name
	* @return The debug combination name.
	*/
	virtual FText GetDebugName_Implementation() override
	{
		return FText::Format(NSLOCTEXT("AP", "GenericCombinationWithSingleItemDebugName", "Generic combination with single item:{0}"), Name);
	}
	/**
	* Retrieves the list of all possible target classes. Constant, getter for TargetClass wrapped in an array. @see UGenericCombinationWithSingleItem#TargetClass
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
	* @return True if the combination is possible, i.e. CombinationTarget inherits from TargetClass otherwise false. @see UGenericCombinationWithSingleItem#TargetClass
	*/
	virtual	bool CanCombineWith_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(CombinationTarget))
		{
			LOG_Warning(NSLOCTEXT("AP", "GenericCombinationWithSingleItem_CanCombineWithNullItem", "GenericCombinationWithSingleItem:CanCombineWith::The other item is null or invalid."));
			return false;
		}
		return CombinationTarget->GetClass()->IsChildOf(TargetClass);
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
	/**
	* Retrieves the type of this combination that can be displayed to the user. Constant, getter for ActionType. @see UGenericCombinationWithSingleItem#ActionType
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