#include "StartDialogCombinationAction.h"
#include "BlueprintLibrary/AdventurePluginBlueprintLibrary.h"

void UStartDialogCombinationAction::Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	UAdventurePluginBlueprintLibrary::ShowDialogFromEntryPoint(GameContextOverride, DialogToStart, this);
}