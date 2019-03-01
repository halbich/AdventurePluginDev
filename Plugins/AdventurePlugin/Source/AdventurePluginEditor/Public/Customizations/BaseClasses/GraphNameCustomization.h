#pragma once

#include "CoreMinimal.h"
#include "Customizations/BaseClasses/ComboBoxPropertyTypeCustomization.h"

/**
* A base class for property editor customizations for a struct that contains both a graph (child of UGenericGraph) and a FName property,
* which allows the user to select first the graph and then the FName from the ComboBox based on that graph.
*/
class ADVENTUREPLUGINEDITOR_API FGraphNameCustomization : public FComboBoxPropertyTypeCustomization
{
public:

	/**
	* Shows one-line description of a value of this structs, which is useful mostly when the struct
	* is collapsed in property editor. By default, it displays the name of the graph, followed by the selected FName.
	*/
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	/**
	* Customize the child properties of the customized struct. By default, this replaces the FName
	* property defined by GetIdPropertyHandle method with a combobox.
	*/
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	/**
	* Retrieves the label of this ComboBox, which will be displayed next
	* to it in property editor. Returns 'name' by default.
	*/
	virtual FText GetComboBoxName() const override;

	/**
	* Returns the one-line description of a value of this struct.
	*/
	virtual FText GetHeaderRowName(TSharedRef<IPropertyHandle> StructPropertyHandle) const;

	/**
	* Retrieves the UGenericGraph property of the customized struct, from which the data
	* for the ComboBox should be extracted. Must be implemented in derived classes!
	*/
	virtual TSharedPtr<IPropertyHandle> GetGraphPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const = 0;

	/**
	* Handle to the UGenericGraph property on the customized struct.
	*/
	TSharedPtr<IPropertyHandle> GraphHandle;
};