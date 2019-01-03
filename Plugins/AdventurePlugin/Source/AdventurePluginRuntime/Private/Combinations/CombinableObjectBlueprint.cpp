#pragma once
#include "CombinableObjectBlueprint.h"
#include "CombinableObject.h"
#include "AssetRegistryModule.h"

void UCombinableObjectBlueprint::Compiled(UBlueprint* CompiledBlueprint)
{
	auto* item = Cast<UCombinableObject>(GeneratedClass->ClassDefaultObject);
	if (item == nullptr || !item->IsValidLowLevel())
	{
		return;
	}
	item->RefreshCombinations();
	UpdateExternalCombinations(item);
}
void UCombinableObjectBlueprint::UpdateExternalCombinations(UCombinableObject* RepresentedObject)
{
	RepresentedObject->ExternalBlueprintCombinations.Empty();
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	const UClass* blueprintClass = UCombinableObjectBlueprint::StaticClass();
	AssetRegistryModule.Get().GetAssetsByClass(blueprintClass->GetFName(), AssetData, true);
	for (auto asset: AssetData)
	{ 
		auto* targetObject = GetCombinableObjectFromAsset(asset);
		if (targetObject == nullptr || targetObject == RepresentedObject)
		{
			continue;
		}
		targetObject->ExternalBlueprintCombinations.Remove(this);
		RegisterExternalCombinations(RepresentedObject, targetObject);
		RegisterExternalCombinations(targetObject, RepresentedObject);
	}
}

void UCombinableObjectBlueprint::RegisterExternalCombinations(UCombinableObject* SourceObject, UCombinableObject* TargetObject)
{
	bool foundTarget = false;
	auto* targetBlueprint = TargetObject ? Cast<UBlueprint>(TargetObject->GetClass()->ClassGeneratedBy) : nullptr;
	auto* sourceBlueprint = SourceObject ? Cast<UBlueprint>(SourceObject->GetClass()->ClassGeneratedBy) : nullptr;
	if (targetBlueprint == nullptr || sourceBlueprint == nullptr)
	{
		check(false && "Target and source blueprints should never be nil.")
		return;
	}
	for (auto combination : SourceObject->LocalCombinations)
	{
		if (combination.TargetBlueprints.Contains(targetBlueprint))
		{
			if (foundTarget)
			{
				// TODO: Raise warning
			}
			foundTarget = true;
			TargetObject->ExternalBlueprintCombinations.Add(sourceBlueprint, combination.Name);
		}
	}
}

UCombinableObject* UCombinableObjectBlueprint::GetCombinableObjectFromAsset(FAssetData& AssetData)
{
	auto* assetObject = AssetData.GetAsset();
	auto* assetCasted = Cast<UCombinableObjectBlueprint>(assetObject);
	if (assetCasted == nullptr || !assetCasted->IsValidLowLevel())
	{
		return nullptr;
	}
	auto* assetCDO = assetCasted->GeneratedClass ? assetCasted->GeneratedClass->ClassDefaultObject : nullptr;
	if (assetCDO == nullptr || !assetCDO->IsValidLowLevel())
	{
		return nullptr;
	}
	auto* targetCombinableObject = Cast<UCombinableObject>(assetCDO);
	if (targetCombinableObject == nullptr)
	{
		return nullptr;
	}
	return targetCombinableObject;
}