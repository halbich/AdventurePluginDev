#include "CombinationTriggerBase.h"

TArray<UClass*> UCombinationTriggerBase::GetCombinationTargetClasses_Implementation()
{
	check(false && "This method must be overriden");
	return TArray<UClass*>();
}

bool UCombinationTriggerBase::CanCombineWith_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	check(false && "This method must be overriden");
	return false;
}