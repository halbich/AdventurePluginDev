#pragma once

#include "Core.h"
#include "Delegate.h"
#include "InventoryItem.h"
#include "CombinationInterface.h"
#include "UseActionType.h"
#include "SimpleCombinationWithSingleItem.generated.h"

class UAdventurePluginGameContext;

/*Represents the simple A+B=C combination. I.e. if you combine this item with item B, both A and B will be removed from inventory and C will be added.*/
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API USimpleCombinationWithSingleItem : public UObject, public ICombinationInterface
{
	GENERATED_BODY()

public:
	/*The name of this combination.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;
	/*The type of action of this combination.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FUseActionType ActionType;
	/*The event to be executed when Execute is called.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UInventoryItem> ResultItemClass;
	/*The single target class of this combination.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCombinableObject> TargetClass;

	virtual FText GetName_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override
	{
		return Name;
	}

	virtual FText GetDebugName_Implementation() override
	{
		return FText::Format(NSLOCTEXT("AP", "SimpleCombinationWithSingleItemDebugName", "Simple combination with single item:{0}"), Name);
	}

	virtual TArray<UClass*> GetCombinationTargetClasses_Implementation() override
	{
		TArray<UClass*> ToReturn = TArray<UClass*>();
		ToReturn.Add(TargetClass);
		return ToReturn;
	}

	FUseActionType GetUseActionType_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext)
	{
		return ActionType;
	}

	virtual void Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override;

	virtual	bool CanCombineWith_Implementation(UObject* CombinationSource, UObject* CombinationTarget);
};