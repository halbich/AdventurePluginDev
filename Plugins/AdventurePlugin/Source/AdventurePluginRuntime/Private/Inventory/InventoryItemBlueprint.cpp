#include "InventoryItemBlueprint.h"

#pragma optimize("", off)
UTexture2D* UInventoryItemBlueprint::GetIcon() const
{
	if (this->GeneratedClass == nullptr || !this->GeneratedClass->IsValidLowLevel() ||
		this->GeneratedClass->ClassDefaultObject == nullptr || !this->GeneratedClass->ClassDefaultObject->IsValidLowLevel())
	{
		return nullptr;
	}
	auto* item = Cast<UInventoryItem>(this->GeneratedClass->ClassDefaultObject);
	if (item == nullptr || !item->IsValidLowLevel())
	{
		return nullptr;
	}
	return item->Icon;
}

UInventoryItem * UInventoryItemBlueprint::GetItemInstance(UAdventurePluginGameContext* GameContext)
{
	if (GameContext == nullptr || !GameContext->IsValidLowLevel() ||
		GameContext->ItemManager == nullptr || !GameContext->ItemManager->IsValidLowLevel() ||
		this->GeneratedClass == nullptr || !this->GeneratedClass->IsValidLowLevel())
	{
		return nullptr;
	}
	TSubclassOf<UInventoryItem> itemClass = (TSubclassOf<UInventoryItem>)(this->GeneratedClass);
	return GameContext->ItemManager->GetItem(itemClass);
}
void UInventoryItemBlueprint::Compiled(UBlueprint* CompiledBlueprint)
{
	auto* item = Cast<UInventoryItem>(GeneratedClass->ClassDefaultObject);
	if (item == nullptr || !item->IsValidLowLevel())
	{
		return;
	}
	item->ParentBlueprint = this;
	item->RefreshCombinations();
}
#pragma optimize("", on)