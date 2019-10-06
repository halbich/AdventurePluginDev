#include "CombinationActionBase.h"

void UCombinationActionBase::Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	check(false && "This method must be overriden");
}