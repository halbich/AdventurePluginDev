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
			LOG_Warning(NSLOCTEXT("AP", "CombinableObjectRefreshCombinationInvalidCombination", "CombinableObject:RefreshCombinations: Found null or invalid combination."));
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

TScriptInterface<ICombinationInterface> UCombinableObject::GetCombinationWithObject(UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContext)
{
	if (!IsValid(OtherObject))
	{
		LOG_Warning(NSLOCTEXT("AP", "NullCombinationItem", "One of the items being combined is null."));
		return false;
	}
	TScriptInterface<ICombinationInterface> FoundCombination = GetCombinationWithObjectLocalOnly(OtherObject, GameContext);
	if (!IsValid(FoundCombination.GetObject()))
	{
		FoundCombination = OtherObject->GetCombinationWithObjectLocalOnly(this, GameContext);
	}
	return FoundCombination;
}

bool UCombinableObject::TryCombineWith(UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContext)
{
	TScriptInterface<ICombinationInterface> CombinationToExecute = GetCombinationWithObject(OtherObject, GameContext);
	if (!IsValid(CombinationToExecute.GetObject()))
	{
		return false;
	}
	ExecuteCombination(CombinationToExecute, OtherObject, GameContext);
	return true;
}

void UCombinableObject::ExecuteCombination(TScriptInterface<ICombinationInterface> Combination, UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContext)
{
	if (!IsValid(Combination.GetObject()))
	{
		LOG_Warning(NSLOCTEXT("AP", "CombinableObjectExecuteCombination_NullCombination", "UCombinableObject:ExecuteCombination: Combination is null or invalid."));
	}
	// Make sure that we are executing the combination with correct source and target object - This is source if the combination was defined here.
	if (Combinations.Contains(Combination))
	{
		Combination->Execute_Execute(Combination.GetObject(), this, OtherObject, GameContext);
	}
	else
	{
		Combination->Execute_Execute(Combination.GetObject(), OtherObject, this, GameContext);
	}
}

TScriptInterface<ICombinationInterface> UCombinableObject::GetCombinationWithObjectLocalOnly(UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContext)
{
	for (TScriptInterface<ICombinationInterface>& CombinationInterface : Combinations)
	{
		if (!IsValid(CombinationInterface.GetObject()))
		{
			continue;
		}
		UObject* CombinationObject = CombinationInterface.GetObject();
		if (!CombinationInterface->Execute_CanCombineWith(CombinationObject, this, OtherObject, GameContext))
		{
			continue;
		}
		return CombinationInterface;
	}
	return nullptr;
}
#pragma optimize("", on)