#pragma once

#include "CoreMinimal.h"
#include "PropertyHandle.h"
#include "Customizations/BaseClasses/GraphNameCustomization.h"

/**
* Property editor customization for FQuestGraphFlag struct which replaces its
* FQuestGraphFlag#FlagName property with a ComboBox picker that allows the user to select from
* flags defined in the Quest graph.
* @see FQuestGraphFlag
*/
class FQuestGraphFlagCustomization : public FGraphNameCustomization
{
public:

	/**
	* Creates an instance of FQuestGraphFlagCustomization
	*/
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	/**
	* Retrieves the FQuestGraphFlag#Quest property of the FQuestGraphFlag, from which
	* the flags for the ComboBox should be extracted.
	*/
	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	/**
	* Retrieves the FQuestGraphFlag#FlagName property of the FQuestGraphFlag, which should
	* be represented as a ComboBox.
	*/
	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	/**
	* Fills the flags defined in the Quest graph to the FComboBoxCustomizationBase#Options
	* array when the ComboBox reloads.
	*/
	virtual void ReloadOptions() override;
};