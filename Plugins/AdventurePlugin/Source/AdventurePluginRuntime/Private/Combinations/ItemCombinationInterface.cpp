#include "ItemCombinationInterface.h"

FText IItemCombinationInterface::GetName_Implementation()
{
	return FText();
}

TArray<UClass*> IItemCombinationInterface::GetCombinationTargetClasses_Implementation()
{
	return TArray<UClass*>();
}

UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
bool IItemCombinationInterface::CanCombineWith_Implementation(UObject* CombinationTarget)
{
	return false;
}

void IItemCombinationInterface::Execute_Implementation(UObject* CombinationTarget, UAdventurePluginGameContext* GameContext)
{

}