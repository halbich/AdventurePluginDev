#include "Customizations/UseActionTypeCustomization.h"
#include "Inventory/Structs/UseActionType.h"
#include "Common/AdventurePluginConfig.h"

#define LOCTEXT_NAMESPACE "UseActionTypeCustomization"

TSharedRef<IPropertyTypeCustomization> FUseActionTypeCustomization::MakeInstance()
{
	return MakeShareable(new FUseActionTypeCustomization);
}

void FUseActionTypeCustomization::ReloadOptions()
{
	UAdventurePluginConfig* Settings = GetMutableDefault<UAdventurePluginConfig>();
	for (FName& Name : Settings->UseActionTypes)
	{
		FComboItemType NewItem = MakeShareable(new FName(Name));
		Options.Add(NewItem);
	}
}

FText FUseActionTypeCustomization::GetComboBoxName() const
{
	return LOCTEXT("UseActionType", "Use Action Type");
}

TSharedPtr<IPropertyHandle> FUseActionTypeCustomization::GetIdPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle) const
{
	return StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FUseActionType, UseActionTypeName));
}

#undef LOCTEXT_NAMESPACE