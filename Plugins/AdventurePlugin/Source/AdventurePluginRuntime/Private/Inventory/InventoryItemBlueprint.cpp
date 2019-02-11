#include "InventoryItemBlueprint.h"

#pragma optimize("", off)
UTexture2D* UInventoryItemBlueprint::GetIcon() const
{
	if (this->GeneratedClass == nullptr || !this->GeneratedClass->IsValidLowLevel() ||
		this->GeneratedClass->ClassDefaultObject == nullptr || !this->GeneratedClass->ClassDefaultObject->IsValidLowLevel())
	{
		// TODO: Log error.
		return nullptr;
	}
	UInventoryItem* ItemInstance = Cast<UInventoryItem>(this->GeneratedClass->ClassDefaultObject);
	if (ItemInstance == nullptr || !ItemInstance->IsValidLowLevel())
	{
		// TODO: Log error.
		return nullptr;
	}
	return ItemInstance->Icon;
}

UInventoryItem * UInventoryItemBlueprint::GetItemInstance(UAdventurePluginGameContext* GameContext)
{
	if (GameContext == nullptr || !GameContext->IsValidLowLevel() ||
		GameContext->ItemManager == nullptr || !GameContext->ItemManager->IsValidLowLevel() ||
		this->GeneratedClass == nullptr || !this->GeneratedClass->IsValidLowLevel())
	{
		return nullptr;
	}
	TSubclassOf<UInventoryItem> ItemClass = (TSubclassOf<UInventoryItem>)(this->GeneratedClass);
	return GameContext->ItemManager->GetItem(ItemClass);
}
#pragma optimize("", on)