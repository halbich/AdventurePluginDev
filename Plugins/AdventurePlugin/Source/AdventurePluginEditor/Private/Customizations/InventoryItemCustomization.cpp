#include "Customizations/InventoryItemCustomization.h"
#include "Common/AdventurePluginConfig.h"
#include "Inventory/InventoryItem.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "InventoryItemCustomization"

TSharedRef<IDetailCustomization> FInventoryItemCustomization::MakeInstance()
{
	return MakeShareable(new FInventoryItemCustomization);
}

void FInventoryItemCustomization::SetIdHandle(IDetailLayoutBuilder& DetailLayout)
{
	IdHandle = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UInventoryItem, UseActionType));
}

FText FInventoryItemCustomization::GetComboBoxName()
{
	return LOCTEXT("UseActionType", "Use Action Type");
}

TSet<FComboBoxCustomization::FComboItemType> FInventoryItemCustomization::GetComboBoxOptions(UObject* ObjectBeingCustomized)
{
	TSet<FComboItemType> Ids;
	UAdventurePluginConfig* Settings = GetMutableDefault<UAdventurePluginConfig>();
	for (FName& Name : Settings->UseActionTypes)
	{
		FComboItemType NewItem = MakeShareable(new FName(Name));
		Ids.Add(NewItem);
	}
	return Ids;
}

#undef LOCTEXT_NAMESPACE 
