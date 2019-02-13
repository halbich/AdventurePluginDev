#include "InventoryItemBlueprint.h"

#pragma optimize("", off)
UTexture2D* UInventoryItemBlueprint::GetIcon() const
{
	if (!IsValid(this->GeneratedClass) || !IsValid(this->GeneratedClass->ClassDefaultObject))
	{
		// TODO: Log error.
		return nullptr;
	}
	UInventoryItem* ItemInstance = Cast<UInventoryItem>(this->GeneratedClass->ClassDefaultObject);
	if (!IsValid(ItemInstance))
	{
		// TODO: Log error.
		return nullptr;
	}
	return ItemInstance->Icon;
}

UInventoryItem * UInventoryItemBlueprint::GetItemInstance(UAdventurePluginGameContext* GameContext)
{
	if (!IsValid(GameContext) || !IsValid(GameContext->ItemManager) || !IsValid(this->GeneratedClass))
	{
		return nullptr;
	}
	TSubclassOf<UInventoryItem> ItemClass = (TSubclassOf<UInventoryItem>)(this->GeneratedClass);
	return GameContext->ItemManager->GetItem(ItemClass);
}
#pragma optimize("", on)