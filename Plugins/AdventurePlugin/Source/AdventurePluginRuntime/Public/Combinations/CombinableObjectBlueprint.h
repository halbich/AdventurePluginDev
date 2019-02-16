#pragma once

#include "Core.h"
#include "Engine/Blueprint.h"
#include "AssetData.h"
#include "CombinableObjectBlueprint.generated.h"

#pragma optimize("", off)
class UCombinableObject;
/**
* Custom blueprint class that makes sure that combinable objects know about combinations defined on other combinable objects.
*/
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UCombinableObjectBlueprint : public UBlueprint
{
	GENERATED_BODY()

public:
	/**
	* The constructor registers a listener to be executed when this class is compiled. 
	*/
	UCombinableObjectBlueprint()
	{
		this->OnCompiled().AddUObject(this, &UCombinableObjectBlueprint::Compiled);
	}
	/**
	* Called when this blueprint is compiled. Recreates all the combinations involving the represented object on the object and on all other combinable objects.
	* @param CompiledBlueprint The blueprint that was just compiled.
	*/
	UFUNCTION()
	void Compiled(UBlueprint* CompiledBlueprint);
private:
	/**
	* Updates external combinations relevant to this object, both those defined on this object and those defined on other objects.
	* @param RepresentedObject The CDO of the class represented by this blueprint, whose list of combinations should be updated.
	*/
	UFUNCTION()
	void UpdateExternalCombinations(UCombinableObject* RepresentedObject);
	/**
	* Converts FAssetData representing a blueprint to the Class default object of the UCombinableObject it represents
	* @param AssetData The data containing the UCombinableObjectBlueprint.
	* @return The CDO of the UCombinableObject class represented by the blueprint in AssetData or nullptr if the conversion is impossible.
	*/
	UFUNCTION()
		UCombinableObject* GetCombinableObjectFromAsset(FAssetData& AssetData);
	/**
	* If there are some, registers on the target object the combinations between source and target object that are defined on the source object.
	* @param SourceObject The object whose combination list is being updated.
	* @param TargetObject The object with whom this object might be combinable.
	*/
	UFUNCTION()
		void RegisterExternalCombinations(UCombinableObject* SourceObject, UCombinableObject* TargetObject);
};
#pragma optimize("", on)