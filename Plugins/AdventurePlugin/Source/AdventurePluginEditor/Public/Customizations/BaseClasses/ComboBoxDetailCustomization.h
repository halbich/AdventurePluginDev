#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "ComboBoxCustomizationBase.h"

/*A base class for customizations adding a combobox picker for an FName property.*/
class ADVENTUREPLUGINEDITOR_API FComboBoxDetailCustomization : public FComboBoxCustomizationBase, public IDetailCustomization
{
public:

	/* Applies the ComboBox customization.*/
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

protected:

	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(IDetailLayoutBuilder& DetailLayout) const = 0;

	UObject* ObjectBeingCustomized;
};