#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "Dialogue/Graph/DialogGraphNode_IfInInventory.h"

class FDialogInventoryItemCustomization : public IDetailCustomization
{
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

protected:

	void OnPickerChanged();

	UDialogGraphNode_IfInInventory* InventoryNode;
	TSharedPtr<IPropertyHandle> PickerHandle;
};