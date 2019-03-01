#pragma once

#include "CoreMinimal.h"
#include "Customizations/BaseClasses/ComboBoxPropertyTypeCustomization.h"
#include "PropertyHandle.h"

/**
* Property editor customization which replaces FUseAction struct with a combobox picker
* that allows the user to select from action types defined in project configuration.
*/
class ADVENTUREPLUGINEDITOR_API FUseActionTypeCustomization : public FComboBoxPropertyTypeCustomization
{

public:

	/**
	* Creates an instance of FUseActionTypeCustomization
	*/
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	/**
	* Fills the Action types defined in project configuration to the Options
	* array when the ComboBox reloads.
	*/
	virtual void ReloadOptions() override;

	/**
	* Retrieves the label of this ComboBox, which will be displayed next
	* to it in property editor.
	*/
	virtual FText GetComboBoxName() const override;

	/**
	* Retrieves the FName property of the FUseAction struct, which should be represented as a ComboBox.
	*/
	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;
};