#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "Quest/Graph/QuestGraphNode_Inventory.h"

class FQuestInventoryItemCustomization : public IDetailCustomization
{
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

protected:

	void OnPickerChanged();

	UQuestGraphNode_Inventory* InventoryNode;
	TSharedPtr<IPropertyHandle> PickerHandle;
};