#pragma once

#include "CoreMinimal.h"
#include "PropertyHandle.h"
#include "Customizations/BaseClasses/GraphNameCustomization.h"

/**
* Property editor customization for FDialogGraphEntryPoint struct which replaces its
* EntryPointName property with a combobox picker that allows the user to select from
* entry points defined in the Dialog graph.
*/
class FDialogGraphEntryPointCustomization : public FGraphNameCustomization
{
public:

	/**
	* Creates an instance of FDialogGraphEntryPointCustomization
	*/
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	/**
	* Retrieves the DialogGraph property of the FDialogGraphEntryPoint, from which
	* the entry points for the ComboBox should be extracted.
	*/
	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	/**
	* Retrieves the EntryPointName property of the FDialogGraphEntryPoint, which should
	* be represented as a ComboBox.
	*/
	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	/**
	* Fills the entry points defined in the Dialog graph to the Options
	* array when the ComboBox reloads.
	*/
	virtual void ReloadOptions() override;
};