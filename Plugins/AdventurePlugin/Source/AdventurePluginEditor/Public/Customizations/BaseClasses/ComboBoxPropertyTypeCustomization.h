#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"
#include "ComboBoxCustomizationBase.h"

/**
* A base class for customizations adding a combobox picker for an FName property, which is a part of some sturct.
*/
class ADVENTUREPLUGINEDITOR_API FComboBoxPropertyTypeCustomization : public FComboBoxCustomizationBase, public IPropertyTypeCustomization
{
public:

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const = 0;
};