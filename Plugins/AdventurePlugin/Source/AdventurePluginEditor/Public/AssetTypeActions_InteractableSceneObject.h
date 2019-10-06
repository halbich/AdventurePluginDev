#pragma once

#include "CoreMinimal.h"
#include "InteractableSceneObject.h"
#include "AssetTypeActions_Base.h"

/**
* Action for creating UInteractableSceneObject asset representing one object on the scene.
* However, the asset created will actually be of type UCombinableObjectBlueprint.
* @see UInteractableSceneObject
* @see UCombinableObjectBlueprint
*/
class FAssetTypeActions_InteractableSceneObject : public FAssetTypeActions_Base
{
public:

	/**
	* @param InAssetCategory Asset categories of this asset
	*/
	FAssetTypeActions_InteractableSceneObject(EAssetTypeCategories::Type InAssetCategory)
		: MyAssetCategory(InAssetCategory)
	{
	}

	/**
	* Returns the name of the asset type created with this action.
	* @return Name of the asset type
	*/
	virtual FText GetName() const override
	{
		return NSLOCTEXT("AssetTypeActions_InteractableSceneObject", "AssetName", "Interactable Scene Object");
	}

	/**
	* Returns the color associated with this asset type in UE editor.
	* @return Color of this asset type
	*/
	virtual FColor GetTypeColor() const override
	{
		return FColor(127, 255, 255);
	}

	/**
	* Returns the asset type for which this action is registered.
	* @return Asset type, in this case UAdventureCharacter
	*/
	virtual UClass* GetSupportedClass() const override
	{
		return UInteractableSceneObject::StaticClass();
	}

	/**
	* Returns the asset categories in which this action will be placed.
	* @return Asset categories of this asset
	*/
	virtual uint32 GetCategories() override
	{
		return MyAssetCategory;
	}

	/**
	* Returns the description of this asset type.
	* @return Description of the asset type
	*/
	virtual FText GetAssetDescription(const FAssetData& AssetData) const override
	{
		return NSLOCTEXT("AssetTypeActions_InteractableSceneObject", "AssetDescription", "Interactable Scene Object");
	}

private:

	/** Asset categories of this asset */
	EAssetTypeCategories::Type MyAssetCategory;
};