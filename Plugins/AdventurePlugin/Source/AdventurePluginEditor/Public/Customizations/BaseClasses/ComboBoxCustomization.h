#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
/*A base class for customizations adding a combobox picker for an FName property.*/
class ADVENTUREPLUGINEDITOR_API FComboBoxCustomization : public IDetailCustomization
{
public:
	/*The type of an item in the combobox.*/
	typedef TSharedPtr<FName> FComboItemType;
	/* Applies the ComboBox customization.*/
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

protected:
	// Sets the handle to the property this ComboBox is editing. Must be overriden.
	virtual void SetIdHandle(IDetailLayoutBuilder& DetailLayout);
	// Retrieves the display name of this ComboBox. Must be overriden.
	virtual FText GetComboBoxName();
	/*Retireves the options to be displayed in this ComboBox.*/
	virtual TSet<FComboItemType> GetComboBoxOptions(UObject* ObjectBeingCustomized);
	/* Retrieves the display name of the currently selected item.*/
	virtual FText GetCurrentItemLabel() const;
	/*Generates the name widget.*/
	virtual TSharedRef<SWidget> MakeWidgetForName(FComboItemType InOption);
	/*Called when the ComboBox selection changes.*/
	virtual void OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type);
	/*The options displayed in the ComboBox.*/
	TArray<FComboItemType> Options;
	/*Handle to the property this ComboBox represents.*/
	TSharedPtr<IPropertyHandle> IdHandle;
};