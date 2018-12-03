#pragma once

#include "Core.h"
#include "Delegate.h"
#include "ItemCombination.generated.h"

class UInventoryItem;
class UAdventurePluginGameContext;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FCombinationEvent, UInventoryItem*, OtherItem, UAdventurePluginGameContext*, Context);

UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UItemCombination : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Name;

	UPROPERTY(BlueprintReadWrite)
		FCombinationEvent CombinationEvent;
};