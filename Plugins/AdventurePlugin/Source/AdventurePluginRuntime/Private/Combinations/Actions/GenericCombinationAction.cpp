#include "GenericCombinationAction.h"
#include "Common/AdventurePluginGameContext.h"
#include "BlueprintLibrary/AdventurePluginBlueprintLibrary.h"

void UGenericCombinationAction::Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
	CombinationEvent.Execute(CombinationTarget, GameContext);
}