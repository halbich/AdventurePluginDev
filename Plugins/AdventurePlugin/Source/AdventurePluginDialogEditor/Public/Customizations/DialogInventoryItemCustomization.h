#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "Dialog/Graph/DialogGraphNode_IfInInventory.h"

/**
* Property editor customization for UDialogGraphNode_ItemBase class, which propagates
* the inventory item selected from its PickerItem property to the Item property including
* the conversion from UInventoryItemBlueprint to TSubclassOf<UInventoryItem>. The reason
* is that the picker for PickerItem displays thumbnail and is therefore more user-friendly.
*/
class FDialogInventoryItemCustomization : public IDetailCustomization
{
public:

	/**
	* Creates an instance of FDialogInventoryItemCustomization.
	*/
	static TSharedRef<IDetailCustomization> MakeInstance();

	/**
	* Binds the OnPickerChanged method to OnPropertyValueChanged for PickerHandle property.
	*/
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

protected:

	/**
	* Sets the value, converted from the PickerItem property,
	* to the Item property on UDialogGraphNode_ItemBase.
	*/
	void OnPickerChanged();

	UDialogGraphNode_ItemBase* InventoryNode;
	TSharedPtr<IPropertyHandle> PickerHandle;
};