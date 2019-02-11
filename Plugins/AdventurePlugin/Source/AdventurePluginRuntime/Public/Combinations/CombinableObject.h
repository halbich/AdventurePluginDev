#pragma once

#include "Core.h"
#include "LocalCombinationInfo.h"
#include "CombinableObject.generated.h"


class ICombinationInterface;
class UAdventurePluginGameContext;
/*Represents an object that can be combined with other some other object, e.g. inventory items and characters*/
UCLASS(Abstract, BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UCombinableObject : public UObject
{
	GENERATED_BODY()

public:

	/*Call this method to initialize combinations. Must be called before being used.*/
	void Init()
	{
		RefreshCombinations();
	}

#if WITH_EDITORONLY_DATA
	/*This array has informations about all combinations registered on this object. Use only in editor time.*/
	UPROPERTY(VisibleAnywhere)
		TArray<FLocalCombinationInfo> LocalCombinations;

	/*This array has informations about all combinations with this object registered on other blueprint objects.*/
	UPROPERTY(VisibleAnywhere)
		TMap<UBlueprint*, FText> ExternalBlueprintCombinations;
#endif
	/*Registers a new combination on this object. Should be called only in the InitCombinations method, without the plugin might not show the combinations in editor correctly.*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Combinations")
		void AddCombinationObject(TScriptInterface<ICombinationInterface> ToAdd);

	/*Override this method to register combinations. All combinations should be registered in this method. Do not call this method directly*/
	UFUNCTION(BlueprintNativeEvent, Category = "AdventurePlugin|Combinations")
		void InitCombinations();

	/*This method clears the combinations array and then initializes them again.*/
	void RefreshCombinations();
	/*Try to find a combination between this and target object and execute it. Returns true if a combination is found, otherwise false.*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Combinations")
		bool TryCombineWith(UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContext);


protected:
	/*If true, RefreshCombinations method is currently being executed and combinations an be added without warnings.*/
	UPROPERTY(Transient)
		bool bIsRefreshingCombinations;

	/*Show warning if not currently in the process of refreshing combinations.*/
	void CheckIsRefreshingCombinations();

	/*List of all combinations defined on this object.*/
	UPROPERTY(Transient)
		TArray<TScriptInterface<ICombinationInterface>> Combinations;
	/*Helper for TryCombineWith. Tries to combine with target object, but only using combinations defined on this object.*/
	bool TryCombineWithLocalOnly(UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContext);
};