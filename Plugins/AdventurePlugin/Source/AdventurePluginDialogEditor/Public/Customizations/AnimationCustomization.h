#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "Customizations/BaseClasses/ComboBoxDetailCustomization.h"

class FAnimationCustomization : public FComboBoxDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(IDetailLayoutBuilder& DetailLayout) const override;

	virtual FText GetComboBoxName() const override;

	virtual void ReloadOptions() override;
};