#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "Quest/Graph/QuestGraphNode_Inventory.h"
/**
* This customization is for the UQuestGraphNode_Inventory. 
* The node internally uses TSubclassOf<UInventoryItem> to define item in the node.
* However, TSubclass does not have a picker that could display icons.
* To fix that, the user is selecting a UInventoryItemBlueprint, which does have an icon.
* And when the user changes the value of a blueprint, the TSubclassOf<UInventoryItem> is set ti the class that blueprint represents.
*/
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