#pragma once

#include "Core.h"
#include "Delegate.h"
#include "ItemCombinationInterface.h"
#include "ItemCombination.generated.h"

class UInventoryItem;
class UAdventurePluginGameContext;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FCombinationEvent, UInventoryItem*, OtherItem, UAdventurePluginGameContext*, Context);

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
		UClass* TargetClass;

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

	virtual void Execute_Implementation(UInventoryItem* TargetItem, UAdventurePluginGameContext* GameContext) override
	{
		CombinationEvent.Execute(TargetItem, GameContext);
	}
};