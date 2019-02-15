#include "CombinationInterface.h"

FText ICombinationInterface::GetName_Implementation()
{
	return FText();
}

FText ICombinationInterface::GetDebugName_Implementation()
{
	return FText();
}

TArray<UClass*> ICombinationInterface::GetCombinationTargetClasses_Implementation()
{
	return TArray<UClass*>();
}

bool ICombinationInterface::CanCombineWith_Implementation(UObject* CombinationSource, UObject* CombinationTarget)
{
	return false;
}

void ICombinationInterface::Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext)
{

}