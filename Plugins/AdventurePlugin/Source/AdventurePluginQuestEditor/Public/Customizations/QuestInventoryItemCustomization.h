#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "Quest/Graph/QuestGraphNode_Inventory.h"

/**
* Property editor customization for UQuestGraphNode_Inventory class, which propagates
* the inventory item selected from its UQuestGraphNode_Inventory#PickerItem property
* to the UQuestGraphNode_Inventory#Item property including
* the conversion from UInventoryItemBlueprint to TSubclassOf<UInventoryItem>. The reason
* is that the picker for PickerItem displays thumbnail and is therefore more user-friendly.
*/
class FQuestInventoryItemCustomization : public IDetailCustomization
{
public:

	/**
	* Creates an instance of FQuestInventoryItemCustomization.
	*/
	static TSharedRef<IDetailCustomization> MakeInstance();

	/**
	* Binds the OnPickerChanged() method to OnPropertyValueChanged for PickerHandle property.
	*/
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

protected:

	/**
	* Sets the value, converted from the UQuestGraphNode_Inventory#PickerItem property,
	* to the UQuestGraphNode_Inventory#Item property.
	*/
	void OnPickerChanged();

	UQuestGraphNode_Inventory* InventoryNode;
	TSharedPtr<IPropertyHandle> PickerHandle;
};