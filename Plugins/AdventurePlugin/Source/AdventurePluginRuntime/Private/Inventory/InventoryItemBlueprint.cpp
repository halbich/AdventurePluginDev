#include "Inventory/InventoryItemBlueprint.h"

UTexture2D* UInventoryItemBlueprint::GetIcon() const
{
	if (!IsValid(this->GeneratedClass) || !IsValid(this->GeneratedClass->ClassDefaultObject))
	{
		return nullptr;
	}
	UInventoryItem* ItemInstance = Cast<UInventoryItem>(this->GeneratedClass->ClassDefaultObject);
	if (!IsValid(ItemInstance))
	{
		return nullptr;
	}
	return ItemInstance->Icon;
}