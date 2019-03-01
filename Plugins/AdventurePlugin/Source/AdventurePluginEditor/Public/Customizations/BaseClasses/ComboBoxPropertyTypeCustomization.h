#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"
#include "ComboBoxCustomizationBase.h"

/**
* A base class for property editor customizations displaying ComboBox picker
* for an FName property, which is a part of some struct.
*/
class ADVENTUREPLUGINEDITOR_API FComboBoxPropertyTypeCustomization : public FComboBoxCustomizationBase, public IPropertyTypeCustomization
{
public:

	/**
	* Shows one-line description of a value of this structs, which is useful mostly when the struct
	* is collapsed in property editor. By default, it does nothing.
	*/
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	/**
	* Customize the child properties of the customized struct. By default, this replaces the FName
	* property defined by GetIdPropertyHandle method with a combobox.
	*/
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	/**
	* Retrieves the FName property of the customized struct, which should be represented as a ComboBox.
	* Must be implemented in derived classes!
	*/
	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const = 0;
};