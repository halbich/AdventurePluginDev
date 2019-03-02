#pragma once

#include "CoreMinimal.h"
#include "PropertyHandle.h"
#include "Customizations/BaseClasses/GraphNameCustomization.h"

/**
* Property editor customization for FQuestGraphBool struct which replaces its
* FQuestGraphBool#BoolName property with a ComboBox picker that allows the user to select from
* bool variables defined in the Quest graph.
* @see FQuestGraphBool
*/
class FQuestGraphBoolCustomization : public FGraphNameCustomization
{
public:

	/**
	* Creates an instance of FQuestGraphBoolCustomization
	*/
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	/**
	* Retrieves the FQuestGraphBool#Quest property of the FQuestGraphBool, from which
	* the variables for the ComboBox should be extracted.
	*/
	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	/**
	* Retrieves the FQuestGraphBool#BoolName property of the FQuestGraphBool, which should
	* be represented as a ComboBox.
	*/
	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	/**
	* Fills the variables defined in the Quest graph to the FComboBoxCustomizationBase#Options
	* array when the ComboBox reloads.
	*/
	virtual void ReloadOptions() override;
};