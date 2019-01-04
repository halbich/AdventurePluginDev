#include "AdventureCharacterBlueprint.h"
#include "AdventureCharacterManager.h"
#include "AdventurePluginGameContext.h"

#pragma optimize("", off)
UTexture2D* UAdventureCharacterBlueprint::GetIcon() const
{
	if (this->GeneratedClass == nullptr || !this->GeneratedClass->IsValidLowLevel() ||
		this->GeneratedClass->ClassDefaultObject == nullptr || !this->GeneratedClass->ClassDefaultObject->IsValidLowLevel())
	{
		return nullptr;
	}
	auto* item = Cast<UAdventureCharacter>(this->GeneratedClass->ClassDefaultObject);
	if (item == nullptr || !item->IsValidLowLevel())
	{
		return nullptr;
	}
	return item->Icon;
}

UAdventureCharacter * UAdventureCharacterBlueprint::GetItemInstance(UAdventurePluginGameContext* GameContext)
{
	if (GameContext == nullptr || !GameContext->IsValidLowLevel() || 
		GameContext->AdventureCharacterManager == nullptr || !GameContext->AdventureCharacterManager->IsValidLowLevel() ||
		this->GeneratedClass == nullptr || !this->GeneratedClass->IsValidLowLevel())
	{
		return nullptr;
	}
	TSubclassOf<UAdventureCharacter> characterClass = (TSubclassOf<UAdventureCharacter>)(this->GeneratedClass);
	//TODO: Create some manager.
	return GameContext->AdventureCharacterManager->GetCharacter(characterClass);
}
#pragma optimize("", on)