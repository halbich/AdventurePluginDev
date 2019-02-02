#pragma once

#include "CoreMinimal.h"
#include "ComboBoxCustomization.h"
#include "IDetailCustomization.h"

class FDialogLineCustomization : public FComboBoxCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void SetIdHandle(IDetailLayoutBuilder& DetailLayout) override;

	virtual FText GetComboBoxName() override;

	virtual TSet<FComboItemType> GetComboBoxOptions(UObject* ObjectBeingCustomized) override;
};