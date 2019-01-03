#pragma once

#include "Core.h"
#include "Engine/Blueprint.h"
#include "AssetData.h"
#include "CombinableObjectBlueprint.generated.h"

class UCombinableObject;
/*Custom blueprint class that makes sure that combinable objects know about each other and about combinations defined on other objets.*/
#pragma optimize("", off)
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UCombinableObjectBlueprint : public UBlueprint
{
	GENERATED_BODY()

public:

	UCombinableObjectBlueprint()
	{
		this->OnCompiled().AddUObject(this, &UCombinableObjectBlueprint::Compiled);
	}
	/*Called when this blueprint is compiled. Recreates all the combinations involving the represented object on this and all other combinable objects.*/
	UFUNCTION()
		void Compiled(UBlueprint* CompiledBlueprint);
private:
	/*Updates external combinations relevant to this object, both those defined on this object and those defiend on other objects.*/
	UFUNCTION()
		void UpdateExternalCombinations(UCombinableObject* RepresentedObject);
	/*Converts FAssetData representing a blueprint to the Class default object of the UCombinableObject it represents, or nullptr if the conversion is impossible*/
	UFUNCTION()
		UCombinableObject* GetCombinableObjectFromAsset(FAssetData& AssetData);
	/*If there is one, registers on the target object the combination between source and target object that is defined on the source object.*/
	UFUNCTION()
		void RegisterExternalCombinations(UCombinableObject* SourceObject, UCombinableObject* TargetObject);
};
#pragma optimize("", on)