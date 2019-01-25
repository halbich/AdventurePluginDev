#include "Customizations/QuestInventoryItemCustomization.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "QuestInventoryItemCustomization"

TSharedRef<IDetailCustomization> FQuestInventoryItemCustomization::MakeInstance()
{
	return MakeShareable(new FQuestInventoryItemCustomization);
}

void FQuestInventoryItemCustomization::OnPickerChanged()
{
	UObject* Obj;
	PickerHandle->GetValue(Obj);
	InventoryNode->Item = Obj 
		? CastChecked<UInventoryItemBlueprint>(Obj)->GeneratedClass 
		: nullptr;
}

void FQuestInventoryItemCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailLayout.GetObjectsBeingCustomized(Objects);
	check(Objects.Num() > 0);
	InventoryNode = CastChecked<UQuestGraphNode_Inventory>(Objects[0]);

	PickerHandle = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UQuestGraphNode_Inventory, PickerItem));
	PickerHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FQuestInventoryItemCustomization::OnPickerChanged));
}

#undef LOCTEXT_NAMESPACE 