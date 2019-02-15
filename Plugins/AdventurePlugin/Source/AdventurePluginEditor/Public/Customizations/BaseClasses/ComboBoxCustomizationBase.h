#pragma once

#include "CoreMinimal.h"
#include "PropertyHandle.h"
#include "Widgets/Input/SComboBox.h"

/*A base class for customizations adding a combobox picker for an FName property.*/
class ADVENTUREPLUGINEDITOR_API FComboBoxCustomizationBase
{
public:
	/*The type of an item in the combobox.*/
	typedef TSharedPtr<FName> FComboItemType;

	virtual ~FComboBoxCustomizationBase();

protected:

	/* Retrieves the display name of the currently selected item.*/
	virtual FText GetCurrentItemLabel() const;

	/*Generates the name widget.*/
	virtual TSharedRef<SWidget> MakeWidgetForName(FComboItemType InOption);

	/*Called when the ComboBox selection changes.*/
	virtual void OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type);

	virtual void ReloadComboBox();

	virtual void ReloadComboBox(FName Name);

	virtual void ReloadOptions() = 0;

	// Retrieves the display label of this ComboBox. Must be overriden.
	virtual FText GetComboBoxName() const = 0;

	/*The options displayed in the ComboBox.*/
	TArray<FComboItemType> Options;

	/*Handle to the property this ComboBox represents.*/
	TSharedPtr<IPropertyHandle> IdHandle;

	TSharedPtr<SComboBox<FComboItemType>> ComboBox;
};