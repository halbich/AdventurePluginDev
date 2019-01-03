#pragma once
#include "CombinableObject.h"
#include "ItemCombinationInterface.h"
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
		auto name = currentCombination->Execute_GetName(currentCombination.GetObject());
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

void UCombinableObject::AddCombinationObject(TScriptInterface<IItemCombinationInterface> ToAdd)
{
	CheckIsRefreshingCombinations();
	Combinations.Add(ToAdd);
}

bool UCombinableObject::TryCombineWith(UCombinableObject* TargetCombinableObject, UAdventurePluginGameContext* Context)
{
	if (TargetCombinableObject == nullptr || !TargetCombinableObject->IsValidLowLevel())
	{
		LOG_Warning(NSLOCTEXT("AP", "NullCombinationItem", "One of the items being combined is null."));
		return false;
	}
	// Try to find a combination on this item
	if (TryCombineWithLocalOnly(TargetCombinableObject, Context))
	{
		return true;
	}
	// Try to find a combination on the target item.
	return TargetCombinableObject->TryCombineWithLocalOnly(this, Context);
}
bool UCombinableObject::TryCombineWithLocalOnly(UCombinableObject* TargetCombinableObject, UAdventurePluginGameContext* Context)
{
	for (auto combination : Combinations)
	{
		if (combination == nullptr)
		{
			continue;
		}
		auto* combinationObject = combination.GetObject();
		if (!combination->Execute_CanCombineWith(combinationObject, TargetCombinableObject))
		{
			continue;
		}
		combination->Execute_Execute(combinationObject, TargetCombinableObject, Context);
		return true;
	}
	return false;
}
#pragma optimize("", on)