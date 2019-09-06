#include "CombinableObjectBlueprint.h"
#include "CombinableObject.h"
#include "AssetRegistryModule.h"
#include "AdventurePluginRuntime.h"

void UCombinableObjectBlueprint::Compiled(UBlueprint* CompiledBlueprint)
{
	// HACK: While this stops external combinations from working, without this creating a shipping build would be impossible.
	return;
#if WITH_EDITOR
	UCombinableObject* RepresentedObject = Cast<UCombinableObject>(GeneratedClass->ClassDefaultObject);
	if (!IsValid(RepresentedObject))
	{
		return;
	}
	RepresentedObject->RefreshCombinations();
	UpdateExternalCombinations(RepresentedObject);
#endif
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
		UCombinableObject* OtherCombinableObject = GetCombinableObjectFromAsset(CombinableObjectBlueprintAsset);
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
	UBlueprint* OtherBlueprint = OtherObject ? Cast<UBlueprint>(OtherObject->GetClass()->ClassGeneratedBy) : nullptr;
	UBlueprint* SourceBlueprint = SourceObject ? Cast<UBlueprint>(SourceObject->GetClass()->ClassGeneratedBy) : nullptr;
	if (OtherBlueprint == nullptr || SourceBlueprint == nullptr)
	{
		check(false && "Target and source blueprints should never be nil.");
		return;
	} 
	for (FLocalCombinationInfo& Combination : SourceObject->LocalCombinations)
	{
		if (Combination.TargetBlueprints.Contains(OtherBlueprint))
		{
			/*Raise a warning if creating another combination between this and target item.*/
			if (OtherObject->ExternalBlueprintCombinations.Contains(SourceBlueprint) ||
				SourceObject->ExternalBlueprintCombinations.Contains(OtherBlueprint))
			{
				LOG_Warning(FText::Format(NSLOCTEXT("AdventurePlugin", "CombinableObjectBlueprint_RegisterExternalCombinationsDuplicate", "RegisterExternalCombinations:: Multiple combinations found between objects {0} and {1}. Behavior is undefined."),
					FText::FromString(SourceBlueprint->GetFriendlyName()),
					FText::FromString(OtherBlueprint->GetFriendlyName())));
			}
			OtherObject->ExternalBlueprintCombinations.Add(SourceBlueprint, Combination.Name);
		}
	}
#endif
}

UCombinableObject* UCombinableObjectBlueprint::GetCombinableObjectFromAsset(FAssetData& AssetData)
{
#if WITH_EDITOR
	UObject* AssetObject = AssetData.GetAsset();
	UCombinableObjectBlueprint* AssetCombinableObject = Cast<UCombinableObjectBlueprint>(AssetObject);
	if (!IsValid(AssetCombinableObject))
	{
		return nullptr;
	}
	UObject* AssetCDO = AssetCombinableObject->GeneratedClass ? AssetCombinableObject->GeneratedClass->ClassDefaultObject : nullptr;
	UCombinableObject* AssetCombinableObjectCDO = Cast<UCombinableObject>(AssetCDO);
	if (!IsValid(AssetCombinableObjectCDO))
	{
		return nullptr;
	}
	return AssetCombinableObjectCDO;
#endif
	return nullptr;
}