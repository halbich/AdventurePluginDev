#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"

class FDialogLineCustomization : public IDetailCustomization
{
public:

	typedef TSharedPtr<FName> FComboItemType;

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

protected:

	virtual FText GetCurrentItemLabel() const;

	TSharedRef<SWidget> MakeWidgetForName(FComboItemType InOption);

	virtual void OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type);

	TArray<FComboItemType> Options;
	TSharedPtr<IPropertyHandle> IdHandle;
};