#pragma once

#include "Core.h"
#include "LocalCombinationInfo.h"
#include "CombinableObject.generated.h"


class IItemCombinationInterface;
class UAdventurePluginGameContext;

UCLASS(Abstract, BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UCombinableObject : public UObject
{
	GENERATED_BODY()

public:

	void Init()
	{
		RefreshCombinations();
	}

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere)
		TArray<FLocalCombinationInfo> LocalCombinations;

	UPROPERTY()
		UBlueprint* ParentBlueprint;
#endif

	UFUNCTION(BlueprintCallable, Category = "Combinations")
		void AddCombinationObject(TScriptInterface<IItemCombinationInterface> ToAdd);

	UFUNCTION(BlueprintNativeEvent, Category = "Combinations")
		void InitCombinations();

	void RefreshCombinations();

	UFUNCTION(BlueprintCallable, Category = "Combinations")
		bool TryCombineWith(UCombinableObject* TargetItem, UAdventurePluginGameContext* Context);


protected:

	UPROPERTY(Transient)
		bool IsInitializingCombinations;

	/*Show warning if not currently in the process of initializing combinations.*/
	void CheckIsInitializingCombinations();
private:

	/*Map of all combinations, key is InventoryItem object type, value is the combination that should be done.*/
	UPROPERTY(Transient)
		TArray<TScriptInterface<IItemCombinationInterface>> Combinations;

	bool TryCombineWithInternal(UCombinableObject* TargetItem, UAdventurePluginGameContext* Context);
};