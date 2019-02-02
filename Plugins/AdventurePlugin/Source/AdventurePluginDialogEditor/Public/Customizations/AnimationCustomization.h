#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "ComboBoxCustomization.h"

class FAnimationCustomization : public FComboBoxCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void SetIdHandle(IDetailLayoutBuilder& DetailLayout) override;

	virtual FText GetComboBoxName() override;

	virtual TSet<FComboItemType> GetComboBoxOptions(UObject* ObjectBeingCustomized) override;
};