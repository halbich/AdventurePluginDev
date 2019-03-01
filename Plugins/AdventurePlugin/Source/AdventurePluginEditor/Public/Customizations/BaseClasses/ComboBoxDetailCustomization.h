#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "ComboBoxCustomizationBase.h"

/**
* A base class for property editor customizations displaying ComboBox picker
* for an FName property directly on some specific UObject.
*/
class ADVENTUREPLUGINEDITOR_API FComboBoxDetailCustomization : public FComboBoxCustomizationBase, public IDetailCustomization
{
public:

	/* 
	* Applies the ComboBox customization. By default, it will hide the FName property
	* defined by GetIdPropertyHandle method and replace it with a ComboBox.
	*/
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

protected:

	/**
	* Retrieves the FName property of the customized object, which should be represented as a ComboBox.
	* Must be implemented in derived classes!
	*/
	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(IDetailLayoutBuilder& DetailLayout) const = 0;

	UObject* ObjectBeingCustomized;
};