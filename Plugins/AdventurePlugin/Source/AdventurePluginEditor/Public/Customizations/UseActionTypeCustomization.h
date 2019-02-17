#pragma once

#include "CoreMinimal.h"
#include "Customizations/BaseClasses/ComboBoxPropertyTypeCustomization.h"
#include "PropertyHandle.h"
/**
* Customization that give FUseAction type a combobox picker that allows the user to select from action types defined in project configuration.
*/
class ADVENTUREPLUGINEDITOR_API FUseActionTypeCustomization : public FComboBoxPropertyTypeCustomization
{

public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual void ReloadOptions() override;

	virtual FText GetComboBoxName() const override;

	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;
};