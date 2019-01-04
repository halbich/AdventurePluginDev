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
	if (!IsRefreshingCombinations)
	{
		LOG_Warning(NSLOCTEXT("AP", "Combinations not refreshing", "Combinations should not be added to an item outside of InitCombinations method and InitCombinations method should not be called outside RefreshCombinations method"));
	}
}
void UCombinableObject::RefreshCombinations()
{
	IsRefreshingCombinations = true;
	Combinations.Empty();
	InitCombinations();
	IsRefreshingCombinations = false;
#if WITH_EDITORONLY_DATA
	LocalCombinations.Empty();
	for (auto entry : Combinations)
	{
		auto currentCombination = entry;
		if (!currentCombination || !currentCombination.GetObject()->IsValidLowLevel())
		{
			continue;
		}
		auto allCombinationTargets = currentCombination->Execute_GetCombinationTargetClasses(currentCombination.GetObject());
		auto name = currentCombination->Execute_GetDebugName(currentCombination.GetObject());
		auto toAdd = FLocalCombinationInfo();
		toAdd.Name = name;
		// Split combination targets into blueprints and classes so we can navigate to the place where the navigations are defined from editor.
		for (auto* targetClass : allCombinationTargets)
		{
			auto* targetBlueprint = targetClass->ClassGeneratedBy ? Cast<UBlueprint>(targetClass->ClassGeneratedBy) : nullptr;
			if (targetBlueprint == nullptr)
			{
				toAdd.TargetClasses.Add(targetClass);
			}
			else 
			{
				toAdd.TargetBlueprints.Add(targetBlueprint);
			}

		}
		LocalCombinations.Add(toAdd);
	}
#endif
}

void UCombinableObject::AddCombinationObject(TScriptInterface<ICombinationInterface> ToAdd)
{
	CheckIsRefreshingCombinations();
	Combinations.Add(ToAdd);
}

bool UCombinableObject::TryCombineWith(UCombinableObject* TargetObject, UAdventurePluginGameContext* Context)
{
	if (TargetObject == nullptr || !TargetObject->IsValidLowLevel())
	{
		LOG_Warning(NSLOCTEXT("AP", "NullCombinationItem", "One of the items being combined is null."));
		return false;
	}
	// Try to find a combination on this item
	if (TryCombineWithLocalOnly(TargetObject, Context))
	{
		return true;
	}
	// Try to find a combination on the target item.
	return TargetObject->TryCombineWithLocalOnly(this, Context);
}
bool UCombinableObject::TryCombineWithLocalOnly(UCombinableObject* TargetObject, UAdventurePluginGameContext* Context)
{
	for (auto combination : Combinations)
	{
		if (combination == nullptr)
		{
			continue;
		}
		auto* combinationObject = combination.GetObject();
		if (!combination->Execute_CanCombineWith(combinationObject, TargetObject))
		{
			continue;
		}
		combination->Execute_Execute(combinationObject, TargetObject, Context);
		return true;
	}
	return false;
}
#pragma optimize("", on)