#pragma once
#include "CombinableObject.h"
#include "CombinationInterface.h"
#include "AdventurePluginGameContext.h"
#include "AdventurePluginRuntime.h"

#pragma optimize("", off)
void UCombinableObject::InitCombinations_Implementation() {

}
void UCombinableObject::CheckIsRefreshingCombinations()
{
	if (!bIsRefreshingCombinations)
	{
		LOG_Warning(NSLOCTEXT("AP", "Combinations not refreshing", "Combinations should not be added to an item outside of InitCombinations method and InitCombinations method should not be called outside RefreshCombinations method"));
	}
}
void UCombinableObject::RefreshCombinations()
{
	bIsRefreshingCombinations = true;
	Combinations.Empty();
	InitCombinations();
	bIsRefreshingCombinations = false;
#if WITH_EDITORONLY_DATA
	LocalCombinations.Empty();
	for (TScriptInterface<ICombinationInterface>& CombinationInterface : Combinations)
	{
		if (!IsValid(CombinationInterface.GetObject()))
		{
			continue;
		}
		TArray<UClass*> AllCombinationTargets = CombinationInterface->Execute_GetCombinationTargetClasses(CombinationInterface.GetObject());
		FText CombinationDebugName = CombinationInterface->Execute_GetDebugName(CombinationInterface.GetObject());
		FLocalCombinationInfo CombinationInfoToAdd = FLocalCombinationInfo();
		CombinationInfoToAdd.Name = CombinationDebugName;
		// Split combination targets into blueprints and classes so we can navigate to the place where the navigations are defined from editor.
		for (UClass* CombinationTargetClass : AllCombinationTargets)
		{
			UBlueprint* CombinationTargetBlueprint = CombinationTargetClass->ClassGeneratedBy ? Cast<UBlueprint>(CombinationTargetClass->ClassGeneratedBy) : nullptr;
			if (CombinationTargetBlueprint == nullptr)
			{
				CombinationInfoToAdd.TargetClasses.Add(CombinationTargetClass);
			}
			else 
			{
				CombinationInfoToAdd.TargetBlueprints.Add(CombinationTargetBlueprint);
			}

		}
		LocalCombinations.Add(CombinationInfoToAdd);
	}
#endif
}

void UCombinableObject::AddCombinationObject(TScriptInterface<ICombinationInterface> ToAdd)
{
	CheckIsRefreshingCombinations();
	Combinations.Add(ToAdd);
}

bool UCombinableObject::TryCombineWith(UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContext)
{
	if (!IsValid(OtherObject))
	{
		LOG_Warning(NSLOCTEXT("AP", "NullCombinationItem", "One of the items being combined is null."));
		return false;
	}
	// Try to find a combination on this item
	if (TryCombineWithLocalOnly(OtherObject, GameContext))
	{
		return true;
	}
	// Try to find a combination on the target item.
	return OtherObject->TryCombineWithLocalOnly(this, GameContext);
}
bool UCombinableObject::TryCombineWithLocalOnly(UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContext)
{
	for (TScriptInterface<ICombinationInterface>& CombinationInterface : Combinations)
	{
		if (CombinationInterface == nullptr)
		{
			continue;
		}
		UObject* CombinationObject = CombinationInterface.GetObject();
		if (!CombinationInterface->Execute_CanCombineWith(CombinationObject, OtherObject))
		{
			continue;
		}
		CombinationInterface->Execute_Execute(CombinationObject, OtherObject, GameContext);
		return true;
	}
	return false;
}
#pragma optimize("", on)