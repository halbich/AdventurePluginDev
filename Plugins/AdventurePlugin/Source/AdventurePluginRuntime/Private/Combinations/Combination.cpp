#include "Combinations/Combination.h"

FText UCombination::GetName_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	check(false && "This method must be overriden");
	return FText();
}

FText UCombination::GetDebugName_Implementation()
{
	check(false && "This method must be overriden");
	return FText();
}

TArray<UClass*> UCombination::GetCombinationTargetClasses_Implementation()
{
	check(false && "This method must be overriden");
	return TArray<UClass*>();
}

bool UCombination::CanCombineWith_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	check(false && "This method must be overriden");
	return false;
}

void UCombination::Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	check(false && "This method must be overriden");
}

FUseActionType UCombination::GetUseActionType_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	check(false && "This method must be overriden");
	return FUseActionType();
}