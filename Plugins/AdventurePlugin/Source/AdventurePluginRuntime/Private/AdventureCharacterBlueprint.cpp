#include "AdventureCharacterBlueprint.h"
#include "AdventureCharacterManager.h"
#include "AdventurePluginGameContext.h"

#pragma optimize("", off)
UTexture2D* UAdventureCharacterBlueprint::GetIcon() const
{
	//TODO: This is here two times, here and for items - make common ancestor with this? 
	if (this->GeneratedClass == nullptr || !this->GeneratedClass->IsValidLowLevel() ||
		this->GeneratedClass->ClassDefaultObject == nullptr || !this->GeneratedClass->ClassDefaultObject->IsValidLowLevel())
	{
		return nullptr;
	}
	UAdventureCharacter* CharacterInstance = Cast<UAdventureCharacter>(this->GeneratedClass->ClassDefaultObject);
	if (CharacterInstance == nullptr || !CharacterInstance->IsValidLowLevel())
	{
		return nullptr;
	}
	return CharacterInstance->Icon;
}

UAdventureCharacter * UAdventureCharacterBlueprint::GetItemInstance(UAdventurePluginGameContext* GameContext)
{
	if (GameContext == nullptr || !GameContext->IsValidLowLevel() || 
		GameContext->AdventureCharacterManager == nullptr || !GameContext->AdventureCharacterManager->IsValidLowLevel() ||
		this->GeneratedClass == nullptr || !this->GeneratedClass->IsValidLowLevel())
	{
		return nullptr;
	}
	TSubclassOf<UAdventureCharacter> CharacterClass = (TSubclassOf<UAdventureCharacter>)(this->GeneratedClass);
	
	return GameContext->AdventureCharacterManager->GetCharacter(CharacterClass);
}
#pragma optimize("", on)