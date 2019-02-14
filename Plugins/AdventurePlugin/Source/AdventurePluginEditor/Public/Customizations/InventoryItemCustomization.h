#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "ComboBoxCustomization.h"

class FInventoryItemCustomization : public FComboBoxCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void SetIdHandle(IDetailLayoutBuilder& DetailLayout) override;

	virtual FText GetComboBoxName() override;

	virtual TSet<FComboItemType> GetComboBoxOptions(UObject* ObjectBeingCustomized) override;
};