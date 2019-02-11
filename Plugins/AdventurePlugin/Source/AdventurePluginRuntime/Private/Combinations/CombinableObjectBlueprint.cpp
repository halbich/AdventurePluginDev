#pragma once
#include "CombinableObjectBlueprint.h"
#include "CombinableObject.h"
#include "AssetRegistryModule.h"
#include "AdventurePluginRuntime.h"

void UCombinableObjectBlueprint::Compiled(UBlueprint* CompiledBlueprint)
{
	UCombinableObject* RepresentedObject = Cast<UCombinableObject>(GeneratedClass->ClassDefaultObject);
	if (RepresentedObject == nullptr || !RepresentedObject->IsValidLowLevel())
	{
		return;
	}
	RepresentedObject->RefreshCombinations();
	UpdateExternalCombinations(RepresentedObject);
}
void UCombinableObjectBlueprint::UpdateExternalCombinations(UCombinableObject* RepresentedObject)
{
#if WITH_EDITOR
	// Retrieve all assets of type CombinableObjectBlueprint.
	RepresentedObject->ExternalBlueprintCombinations.Empty();
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	const UClass* CombinableObjectBlueprintClass = UCombinableObjectBlueprint::StaticClass();
	AssetRegistryModule.Get().GetAssetsByClass(CombinableObjectBlueprintClass->GetFName(), AssetData, true);
	// Go through all assets, retrieve CDO's of classes they represent register external notifications on both the current and target objects.
	for (FAssetData& CombinableObjectBlueprintAsset : AssetData)
	{
		auto* OtherCombinableObject = GetCombinableObjectFromAsset(CombinableObjectBlueprintAsset);
		if (OtherCombinableObject == nullptr || OtherCombinableObject == RepresentedObject)
		{
			continue;
		}
		// Remove the old entry on the other item if exists.
		OtherCombinableObject->ExternalBlueprintCombinations.Remove(this);
		RegisterExternalCombinations(RepresentedObject, OtherCombinableObject);
		RegisterExternalCombinations(OtherCombinableObject, RepresentedObject);
	}
#endif
}

void UCombinableObjectBlueprint::RegisterExternalCombinations(UCombinableObject* SourceObject, UCombinableObject* OtherObject)
{
#if WITH_EDITOR
	auto* OtherBlueprint = OtherObject ? Cast<UBlueprint>(OtherObject->GetClass()->ClassGeneratedBy) : nullptr;
	auto* SourceBlueprint = SourceObject ? Cast<UBlueprint>(SourceObject->GetClass()->ClassGeneratedBy) : nullptr;
	if (OtherBlueprint == nullptr || SourceBlueprint == nullptr)
	{
		check(false && "Target and source blueprints should never be nil.");
		return;
	}
	for (auto combination : SourceObject->LocalCombinations)
	{
		if (combination.TargetBlueprints.Contains(OtherBlueprint))
		{
			/*Raise a warning if creating another combination between this and target item.*/
			if (OtherObject->ExternalBlueprintCombinations.Contains(SourceBlueprint) ||
				SourceObject->ExternalBlueprintCombinations.Contains(OtherBlueprint))
			{
				LOG_Warning(FText::Format(NSLOCTEXT("AP", "RegisterExternalCombinationsDuplicate", "RegisterExternalCombinations:: Multiple combinations found between objects {0} and {1}. Behavior is undefined."),
					FText::FromString(SourceBlueprint->GetFriendlyName()),
					FText::FromString(OtherBlueprint->GetFriendlyName())));
			}
			OtherObject->ExternalBlueprintCombinations.Add(SourceBlueprint, combination.Name);
		}
	}
#endif
}

UCombinableObject* UCombinableObjectBlueprint::GetCombinableObjectFromAsset(FAssetData& AssetData)
{
#if WITH_EDITOR
	UObject* AssetObject = AssetData.GetAsset();
	UCombinableObjectBlueprint* AssetCombinableObject = Cast<UCombinableObjectBlueprint>(AssetObject);
	if (AssetCombinableObject == nullptr || !AssetCombinableObject->IsValidLowLevel())
	{
		return nullptr;
	}
	auto* AssetCDO = AssetCombinableObject->GeneratedClass ? AssetCombinableObject->GeneratedClass->ClassDefaultObject : nullptr;
	auto* AssetCombinableObjectCDO = Cast<UCombinableObject>(AssetCDO);
	if (AssetCombinableObjectCDO == nullptr || !AssetCombinableObjectCDO->IsValidLowLevel())
	{
		return nullptr;
	}
	return AssetCombinableObjectCDO;
#endif
	return nullptr;
}