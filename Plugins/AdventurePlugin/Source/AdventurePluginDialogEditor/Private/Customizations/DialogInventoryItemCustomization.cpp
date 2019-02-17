#include "Customizations/DialogInventoryItemCustomization.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "DialogInventoryItemCustomization"

TSharedRef<IDetailCustomization> FDialogInventoryItemCustomization::MakeInstance()
{
	return MakeShareable(new FDialogInventoryItemCustomization);
}

void FDialogInventoryItemCustomization::OnPickerChanged()
{
	UObject* Obj;
	PickerHandle->GetValue(Obj);
	InventoryNode->Item = Obj 
		? CastChecked<UInventoryItemBlueprint>(Obj)->GeneratedClass 
		: nullptr;
}

void FDialogInventoryItemCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailLayout.GetObjectsBeingCustomized(Objects);
	check(Objects.Num() > 0);
	InventoryNode = CastChecked<UDialogGraphNode_ItemBase>(Objects[0]);

	PickerHandle = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogGraphNode_ItemBase, PickerItem));
	PickerHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FDialogInventoryItemCustomization::OnPickerChanged));
}

#undef LOCTEXT_NAMESPACE 