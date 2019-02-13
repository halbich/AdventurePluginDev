#pragma once

#include "Core.h"
#include "Delegate.h"
#include "CombinableObject.h"
#include "CombinationInterface.h"
#include "SimpleCombination.generated.h"

class UAdventurePluginGameContext;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FCombinationEvent, UObject*, CombinationTarget, UAdventurePluginGameContext*, Context);
/*Represents a combination with a target object, with a specific constant name and an event to be executed when Execute is called.*/
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API USimpleCombination : public UObject, public ICombinationInterface
{
	GENERATED_BODY()

public:
	/*The name of this combination.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Name;
	/*The event to be executed when Execute is called.*/
	UPROPERTY(BlueprintReadWrite)
		FCombinationEvent CombinationEvent;
	/*The single target class of this combination.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<UCombinableObject> TargetClass;
	
	virtual FText GetName_Implementation() override
	{
		return Name;
	}

	virtual FText GetDebugName_Implementation() override
	{
		return FText::Format(NSLOCTEXT("AP", "SimpleCombinationDebugName", "SimpleCombination:{0}"),Name);
	}

	virtual TArray<UClass*> GetCombinationTargetClasses_Implementation() override
	{
		TArray<UClass*> ToReturn = TArray<UClass*>();
		ToReturn.Add(TargetClass);
		return ToReturn;
	}

	virtual void Execute_Implementation(UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override
	{
		CombinationEvent.Execute(CombinationTarget, GameContext);
	}

	virtual	bool CanCombineWith_Implementation(UObject* CombinationTarget)
	{
		return IsValid(CombinationTarget) ? CombinationTarget->GetClass()->IsChildOf(TargetClass) : false;
	}
};