#pragma once

#include "CoreMinimal.h"
#include "Inventory/Structs/UseActionType.h"
#include "WorldContextProvidingObject.h"
#include "Combination.generated.h"

class UAdventurePluginGameContext;
class UCombinationActionBase;
class UCombinationTriggerBase;

/**
* A class representing a single combination.
* The combination happens when the user tries to use one object on another object.
* A class inheriting this interface specifies what combination is possible and what will happen when that combination is executed.
* As there is no design limitation specifying that a combination is paired with a specific object, most methods accept both source and target combination objects parameters.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UCombination: public UWorldContextProvidingObject
{
	GENERATED_BODY()

public:
	/*
	* Action that will be executed when this combination is triggered.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adventure Plugin")
	UCombinationActionBase* CombinationAction;
	/**
	* The trigger that specifies whether this combination will trigger for the two specific items.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adventure Plugin")
	UCombinationTriggerBase* CombinationTrigger;

	/**
	* The name of this combination.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adventure Plugin")
	FText Name;
	
	/**
	* The type of action of this combination.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adventure Plugin")
	FUseActionType ActionType;
	/**
	* Retrieves the priority of this combination. Only positive values are allowed. The higher the value, the higher the priority.
	* If multiple items are applicable to a pair of items, only the one with the highest priority will be considered.
	* @param GameContextOverride Provides access to all Adventure Plugin data and functionality.
	* @return The priority of this combination.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations", meta = (AdvancedDisplay = GameContextOverride))
	int GetPriority(UAdventurePluginGameContext* GameContextOverride);
	
	/**
	* Retrieves the name of this combination that can be displayed to the user.
	* @param CombinationSource The object on which the combination is defined.
	* @param CombinationTarget The other object of the combination.
	* @param GameContextOverride Provides access to all Adventure Plugin data and functionality.
	* @return The name of the combination.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations", meta = (AdvancedDisplay = GameContextOverride))
	FText GetName(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride);

	/**
	* Retrieves the debug name of this combination to be shown in editor.
	* @return The debug combination name.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations")
	FText GetDebugName();

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

	/**
	* Executes the action this combination represents.
	* @param CombinationSource The object on which the combination is defined.
	* @param CombinationTarget The other object of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations", meta = (AdvancedDisplay = GameContextOverride))
	void Execute(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride);

	/**
	* Retrieves the use type of this combination.
	* @param CombinationSource The object on which the combination is defined.
	* @param CombinationTarget The other object of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The action type of this action, e.g. if this is destroying items, putting them together, talking, giving an item etc. Game specific.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AdventurePlugin|Combinations", meta = (AdvancedDisplay = GameContextOverride))
	FUseActionType GetUseActionType(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride);
};
