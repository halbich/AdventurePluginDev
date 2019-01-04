#pragma once
#include "CombinableObjectBlueprint.h"
#include "CombinableObject.h"
#include "AssetRegistryModule.h"
#include "AdventurePluginRuntime.h"

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
	// Retrieve all assets of type CombinableObjectBlueprint.
	RepresentedObject->ExternalBlueprintCombinations.Empty();
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	const UClass* blueprintClass = UCombinableObjectBlueprint::StaticClass();
	AssetRegistryModule.Get().GetAssetsByClass(blueprintClass->GetFName(), AssetData, true);
	// Go through all assets, retrieve CDO's of classes they represent register external notifications on both the current and target objects.
	for (auto asset : AssetData)
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
	auto* targetBlueprint = TargetObject ? Cast<UBlueprint>(TargetObject->GetClass()->ClassGeneratedBy) : nullptr;
	auto* sourceBlueprint = SourceObject ? Cast<UBlueprint>(SourceObject->GetClass()->ClassGeneratedBy) : nullptr;
	if (targetBlueprint == nullptr || sourceBlueprint == nullptr)
	{
		check(false && "Target and source blueprints should never be nil.");
		return;
	}
	for (auto combination : SourceObject->LocalCombinations)
	{
		if (combination.TargetBlueprints.Contains(targetBlueprint))
		{
			/*Raise a warning if creating another combination between this and target item.*/
			if (TargetObject->ExternalBlueprintCombinations.Contains(sourceBlueprint) || 
				SourceObject->ExternalBlueprintCombinations.Contains(targetBlueprint))
			{
				LOG_Warning(FText::Format(NSLOCTEXT("AP", "RegisterExternalCombinationsDuplicate", "RegisterExternalCombinations:: Multiple combinations found between objects {0} and {1}. Behavior is undefined."),
					FText::FromString(sourceBlueprint->GetFriendlyName()),
					FText::FromString(targetBlueprint->GetFriendlyName())));
			}
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