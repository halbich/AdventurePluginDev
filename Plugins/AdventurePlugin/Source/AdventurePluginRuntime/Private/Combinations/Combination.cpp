#include "Combinations/Combination.h"
#include "Combinations/Actions/CombinationActionBase.h"
#include "Combinations/Triggers/CombinationTriggerBase.h"

FText UCombination::GetName_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	return Name;
}

FText UCombination::GetDebugName_Implementation()
{
	return Name;
}

void UCombination::Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	CombinationAction->Execute(CombinationSource, CombinationTarget, GameContextOverride);
}

TArray<UClass*> UCombination::GetCombinationTargetClasses_Implementation()
{
	return CombinationTrigger->GetCombinationTargetClasses();
}

bool UCombination::CanCombineWith_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	return CombinationTrigger->CanCombineWith(CombinationSource, CombinationTarget, GameContextOverride);
}

FUseActionType UCombination::GetUseActionType_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContextOverride)
{
	return ActionType;
}

int UCombination::GetPriority_Implementation(UAdventurePluginGameContext* GameContextOverride)
{
	check(IsValid(CombinationTrigger));
	if (!IsValid(CombinationTrigger))
	{
		return -1;
	}
	return CombinationTrigger->Priority;
}