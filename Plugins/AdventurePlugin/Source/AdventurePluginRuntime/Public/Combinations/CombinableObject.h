#pragma once

#include "CoreMinimal.h"
#include "LocalCombinationInfo.h"
#include "GameplayTagContainer.h"
#include "WorldContextProvidingObject.h"
#include "CombinableObject.generated.h"

class UCombination;
class UAdventurePluginGameContext;

/**
* Represents an object that can be combined with some other object, e.g. inventory items and characters. Must be overriden.
* All combinations should be added in the InitCombinations() method to allow showing of combinations in editor.
* Init() method must be called before using it, otherwise combinations will not work.
* All non-abstract combinable items should be done in blueprints, otherwise combinations will not work correctly.
*/
UCLASS(Abstract, BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UCombinableObject : public UWorldContextProvidingObject
{
	GENERATED_BODY()

public:

	/**
	* Call this method to initialize combinations. Must be called before being used.
	*/
	virtual void Init()
	{
		RefreshCombinations();
	}

	/**
	* Tags assigned to this object, e.g. weapon, critical, red herring etc.
	* No inherent function unless designers make it so.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interactable object")
		FGameplayTagContainer ObjectTags;

#if WITH_EDITORONLY_DATA
	/**
	* Editor only. This array has informations about all combinations registered on this object. Use only in editor time.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Adventure Plugin")
	TArray<FLocalCombinationInfo> LocalCombinations;

	/**
	* Editor only. This array has informations about all combinations with this object registered on other blueprint objects.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Adventure Plugin")
	TMap<UBlueprint*, FText> ExternalBlueprintCombinations;
#endif

	/**
	* Registers a new combination on this object.
	* Do not call outside of the InitCombinations() method, otherwise the combinations will not be displayed correctly.
	* @param ToAdd The combination object that should be added to the list of supported combinations.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Combinations")
	void AddCombinationObject(UCombination* ToAdd);

	/**
	* Override this method to register combinations. All combinations should be registered in this method. Do not call this method directly.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "AdventurePlugin|Combinations")
	void InitCombinations();

	/**
	* This method clears the registered combinations and then initializes them again.
	*/
	void RefreshCombinations();

	/**
	* Tries to find and return a combination between this and a specified object.
	* Do not execute this combination directly, call, ExecuteCombination() on this object.
	* @param OtherObject The object with which this item should be combined.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The combination between the two objects, or null if such a combination does not exist.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Combinations", meta = (AdvancedDisplay = GameContextOverride))
	UCombination* GetCombinationWithObject(UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContextOverride);

	/**
	* Tries to find and execute a combination between this and a specified object.
	* @param OtherObject The object with which this item should be combined.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if the combination was found and executed, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Combinations", meta = (AdvancedDisplay = GameContextOverride))
	bool TryCombineWith(UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContextOverride);

	/**
	* Use this to trigger a combination. Executes the combination, ensuring that source and other objects are set up properly.
	* @param Combination The combination to be executed.
	* @param OtherObject The object with which this item should be combined.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Combinations", meta = (AdvancedDisplay = GameContextOverride))
	void ExecuteCombination(UCombination* Combination, UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContextOverride);

	/*
	* Sets the World object for this object and sets in on all internal combinations.
	* @param WorldObject - The world object to use.
	*/
	void SetWorldObject(UWorld* WorldObject);
protected:

	/**
	* If true, RefreshCombinations() method is currently being executed and combinations an be added without warnings.
	*/
	UPROPERTY(Transient)
	bool bIsRefreshingCombinations;

	/**
	* Show warning if not currently in the process of refreshing combinations.
	*/
	void CheckIsRefreshingCombinations();

	/**
	* List of all combinations defined on this object.
	*/
	UPROPERTY(Transient)
	TArray<UCombination*> Combinations;

	/**
	* Helper for GetCombinationWithObject(). Tries to find a combination with other object, but only using combinations defined on this object.
	* @param OtherObject The combination with which this object should be combined.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UCombination* GetCombinationWithObjectLocalOnly(UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContext);
};