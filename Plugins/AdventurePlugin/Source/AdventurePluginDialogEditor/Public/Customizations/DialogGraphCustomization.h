#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "Dialog/Graph/DialogGraph.h"

class FDialogGraphCustomization : public IDetailCustomization
{
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

protected:

	void OnPlayerChanged();
	void OnNPCChanged();

	UDialogGraph* Graph;
	TSharedPtr<IPropertyHandle> PickerPlayerHandle;
	TSharedPtr<IPropertyHandle> PickerNPCHandle;
};