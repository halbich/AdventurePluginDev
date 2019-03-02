#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "Dialog/Graph/DialogGraph.h"

/**
* Property editor customization for UDialogGraph class, which propagates
* the player and NPC characters selected from its UDialogGraph#PickerPlayerCharacter and UDialogGraph#PickerNPCCharacter
* properties to the UDialogGraph#PlayerCharacter and UDialogGraph#NPCCharacter properties including the conversion
* from UAdventureCharacterBlueprint to TSubclassOf<UAdventureCharacter>. The reason
* is that the picker properties display thumbnails and are therefore more user-friendly.
*/
class FDialogGraphCustomization : public IDetailCustomization
{
public:

	/**
	* Creates an instance of FDialogGraphCustomization.
	*/
	static TSharedRef<IDetailCustomization> MakeInstance();

	/**
	* Binds the OnPlayerChanged() and OnNPCChanged() method to OnPropertyValueChanged for
	* PickerPlayerHandle and PickerNPCHandle property, respectively.
	*/
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

protected:

	/**
	* Sets the value, converted from the UDialogGraph#PickerPlayerCharacter property,
	* to the UDialogGraph#PlayerCharacter property.
	*/
	void OnPlayerChanged();

	/**
	* Sets the value, converted from the UDialogGraph#PickerNPCCharacter property,
	* to the UDialogGraph#NPCCharacter property.
	*/
	void OnNPCChanged();

	UDialogGraph* Graph;
	TSharedPtr<IPropertyHandle> PickerPlayerHandle;
	TSharedPtr<IPropertyHandle> PickerNPCHandle;
};