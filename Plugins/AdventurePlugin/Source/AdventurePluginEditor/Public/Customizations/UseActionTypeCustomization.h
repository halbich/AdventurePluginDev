#pragma once

#include "CoreMinimal.h"
#include "Customizations/BaseClasses/ComboBoxPropertyTypeCustomization.h"
#include "PropertyHandle.h"

class ADVENTUREPLUGINEDITOR_API FUseActionTypeCustomization : public FComboBoxPropertyTypeCustomization
{

public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual void ReloadOptions() override;

	virtual FText GetComboBoxName() const override;

	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const override;
};