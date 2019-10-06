#include "Combinations/CombinableObject.h"
#include "Combinations/Combination.h"
#include "Common/AdventurePluginGameContext.h"
#include "AdventurePluginRuntime.h"

void UCombinableObject::InitCombinations_Implementation()
{
}

void UCombinableObject::CheckIsRefreshingCombinations()
{
	if (!bIsRefreshingCombinations)
	{
		LOG_Warning(NSLOCTEXT("AdventurePlugin", "CombinableObjects_CombinationsNotRefreshing", "Combinations should not be added to an item outside of InitCombinations method and InitCombinations method should not be called outside RefreshCombinations method"));
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
	for (auto* Combination : Combinations)
	{
		if (!IsValid(Combination))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "CombinableObject_RefreshCombinationInvalidCombination", "CombinableObject:RefreshCombinations: Found null or invalid combination."));
			continue;
		}
		TArray<UClass*> AllCombinationTargets = Combination->GetCombinationTargetClasses();
		FText CombinationDebugName = Combination->GetDebugName();
		FLocalCombinationInfo CombinationInfoToAdd = FLocalCombinationInfo();
		CombinationInfoToAdd.Name = CombinationDebugName;
		// Split combination targets into blueprints and classes so we can navigate to the place where the navigations are defined from editor.
		for (UClass* CombinationTargetClass : AllCombinationTargets)
		{
			UBlueprint* CombinationTargetBlueprint = IsValid(CombinationTargetClass) && IsValid(CombinationTargetClass->ClassGeneratedBy) ? Cast<UBlueprint>(CombinationTargetClass->ClassGeneratedBy) : nullptr;
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

void UCombinableObject::AddCombinationObject(UCombination* ToAdd)
{
	CheckIsRefreshingCombinations();
	Combinations.Add(ToAdd);
}

UCombination* UCombinableObject::GetCombinationWithObject(UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContextOverride)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
	if (!IsValid(OtherObject))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "CombinableObject_GetCombination_NullCombinationItem", "One of the items being combined is null."));
		return nullptr;
	}
	UCombination* FoundCombinationLocal = GetCombinationWithObjectLocalOnly(OtherObject, GameContext);
	auto* FoundCombinationOther = OtherObject->GetCombinationWithObjectLocalOnly(this, GameContext);
	int PriorityLocal = FoundCombinationLocal ? FoundCombinationLocal->GetPriority(GameContextOverride) : -1;
	int PriorityOther = FoundCombinationOther ? FoundCombinationOther->GetPriority(GameContextOverride) : -1;
	return PriorityLocal >= PriorityOther ? FoundCombinationLocal : FoundCombinationOther;
}

bool UCombinableObject::TryCombineWith(UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContextOverride)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
	UCombination* CombinationToExecute = GetCombinationWithObject(OtherObject, GameContext);
	if (!IsValid(CombinationToExecute))
	{
		return false;
	}
	ExecuteCombination(CombinationToExecute, OtherObject, GameContext);
	return true;
}

void UCombinableObject::ExecuteCombination(UCombination* Combination, UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContextOverride)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
	if (!IsValid(Combination))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "CombinableObjectExecuteCombination_NullCombination", "UCombinableObject:ExecuteCombination: Combination is null or invalid."));
	}
	// Make sure that we are executing the combination with correct source and target object - This is source if the combination was defined here.
	if (Combinations.Contains(Combination))
	{
		Combination->Execute(this, OtherObject, GameContext);
	}
	else
	{
		Combination->Execute(OtherObject, this, GameContext);
	}
}

UCombination* UCombinableObject::GetCombinationWithObjectLocalOnly(UCombinableObject* OtherObject, UAdventurePluginGameContext* GameContext)
{
	// If it exists, find the combination between these two objects defined on this object with the highest priority. 
	// In case of a tie, choose the one defined first.
	// If none is found, returns nullptr.
	int CurrentMaxPriority = -1;
	UCombination* MaxPriorityCombination = nullptr;
	for (UCombination* Combination : Combinations)
	{
		if (!IsValid(Combination) || Combination->GetPriority(GameContext) < CurrentMaxPriority || !Combination->CanCombineWith(this, OtherObject, GameContext))
		{
			continue;
		}
		MaxPriorityCombination = Combination;
		CurrentMaxPriority = Combination->GetPriority(GameContext);
	}
	return MaxPriorityCombination;
}

void UCombinableObject::SetWorldObject(UWorld* WorldObject)
{
	auto* gameInstance = WorldObject ? WorldObject->GetGameInstance() : nullptr;
	CachedGameInstance = MakeWeakObjectPtr(gameInstance);
	for (auto* combination : Combinations) 
	{
		combination->CachedGameInstance = MakeWeakObjectPtr(gameInstance);
	}
}