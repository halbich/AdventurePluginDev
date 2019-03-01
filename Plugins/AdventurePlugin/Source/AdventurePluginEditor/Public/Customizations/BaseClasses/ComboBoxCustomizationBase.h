#pragma once

#include "CoreMinimal.h"
#include "PropertyHandle.h"
#include "Widgets/Input/SComboBox.h"

/**
* A base class for property editor customizations which displays a ComboBox picker
* for an FName property. Contains useful methods, so all customizations of this
* type should derive from it.
*/
class ADVENTUREPLUGINEDITOR_API FComboBoxCustomizationBase
{
public:

	/**
	* The type of an item in the ComboBox.
	*/
	typedef TSharedPtr<FName> FComboItemType;

	virtual ~FComboBoxCustomizationBase();

protected:

	/**
	* Retrieves the display name of the currently selected item as a text.
	*/
	virtual FText GetCurrentItemLabel() const;

	/**
	* Generates the name widget (STextBlock by default), which should be displayed
	* as item in ComboBox.
	*/
	virtual TSharedRef<SWidget> MakeWidgetForName(FComboItemType InOption);

	/**
	* This method is called when the ComboBox selection changes. It sets
	* the selected value to the IdHandle by default.
	* @param NewValue Combobox item newly selected
	*/
	virtual void OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type);

	/**
	* Reloads options displayed in ComboBox and unselect selected item.
	*/
	virtual void ReloadComboBox();

	/**
	* Reloads options displayed in ComboBox and select the given item.
	* @param Name Item which should be selected after reload
	*/
	virtual void ReloadComboBox(FName Name);

	/**
	* Handles the filling of items to the Options array itself when the
	* ComboBox reloads. Must be implemented in derived classes!
	*/
	virtual void ReloadOptions() = 0;

	/**
	* Retrieves the label of this ComboBox, which will be displayed next
	* to it in property editor. Must be implemented in derived classes!
	*/
	virtual FText GetComboBoxName() const = 0;

	/** 
	* The options displayed in the ComboBox.
	*/
	TArray<FComboItemType> Options;

	/**
	* Handle to the FName property on customized UObject
	* which is represented by this ComboBox.
	*/
	TSharedPtr<IPropertyHandle> IdHandle;

	/**
	* The ComboBox itself.
	*/
	TSharedPtr<SComboBox<FComboItemType>> ComboBox;
};