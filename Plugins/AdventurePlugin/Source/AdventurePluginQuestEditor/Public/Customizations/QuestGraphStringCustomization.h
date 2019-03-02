#pragma once

#include "CoreMinimal.h"
#include "PropertyHandle.h"
#include "Customizations/BaseClasses/GraphNameCustomization.h"

/**
* Property editor customization for FQuestGraphString struct which replaces its
* FQuestGraphString#StringName property with a ComboBox picker that allows the user to select from
* string variables defined in the Quest graph.
* @see FQuestGraphString
*/
class FQuestGraphStringCustomization : public FGraphNameCustomization
{
public:

	/**
	* Creates an instance of FQuestGraphStringCustomization
	*/
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	/**
	* Retrieves the FQuestGraphString#Quest property of the FQuestGraphString, from which
	* the variables for the ComboBox should be extracted.
	*/
	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	/**
	* Retrieves the FQuestGraphString#StringName property of the FQuestGraphString, which should
	* be represented as a ComboBox.
	*/
	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	/**
	* Fills the variables defined in the Quest graph to the FComboBoxCustomizationBase#Options
	* array when the ComboBox reloads.
	*/
	virtual void ReloadOptions() override;
};