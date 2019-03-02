#pragma once

#include "CoreMinimal.h"
#include "PropertyHandle.h"
#include "Customizations/BaseClasses/GraphNameCustomization.h"

/**
* Property editor customization for FQuestGraphEvent struct which replaces its
* FQuestGraphEvent#EventName property with a ComboBox picker that allows the user to select from
* events defined in the Quest graph.
* @see FQuestGraphEvent
*/
class FQuestGraphEventCustomization : public FGraphNameCustomization
{
public:

	/**
	* Creates an instance of FQuestGraphEventCustomization
	*/
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	/**
	* Retrieves the FQuestGraphEvent#Quest property of the FQuestGraphEvent, from which
	* the events for the ComboBox should be extracted.
	*/
	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	/**
	* Retrieves the FQuestGraphEvent#EventName property of the FQuestGraphEvent, which should
	* be represented as a ComboBox.
	*/
	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;

	/**
	* Fills the events defined in the Quest graph to the FComboBoxCustomizationBase#Options
	* array when the ComboBox reloads.
	*/
	virtual void ReloadOptions() override;
};