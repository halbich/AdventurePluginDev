#pragma once

#include "Core.h"
#include "Delegate.h"
#include "CombinableObject.h"
#include "ItemCombinationInterface.h"
#include "ItemCombination.generated.h"

class UAdventurePluginGameContext;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FCombinationEvent, UObject*, CombinationTarget, UAdventurePluginGameContext*, Context);

UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UItemCombination : public UObject, public IItemCombinationInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Name;

	UPROPERTY(BlueprintReadWrite)
		FCombinationEvent CombinationEvent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<UCombinableObject> TargetClass;

	virtual FText GetName_Implementation() override
	{
		return Name;
	}

	virtual TArray<UClass*> GetCombinationTargetClasses_Implementation() override
	{
		auto toReturn = TArray<UClass*>();
		toReturn.Add(TargetClass);
		return toReturn;
	}

	virtual void Execute_Implementation(UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override
	{
		CombinationEvent.Execute(CombinationTarget, GameContext);
	}

	virtual	bool CanCombineWith_Implementation(UObject* CombinationTarget)
	{
		return CombinationTarget && CombinationTarget->IsValidLowLevel() ? CombinationTarget->GetClass()->IsChildOf(TargetClass) : false;
	}
};