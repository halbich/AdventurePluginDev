#include "AdventureCharacterBlueprint.h"
#include "AdventureCharacterManager.h"
#include "AdventurePluginGameContext.h"

#pragma optimize("", off)
UTexture2D* UAdventureCharacterBlueprint::GetIcon() const
{
	//TODO: This is here two times, here and for items - make common ancestor with this? 
	if (!IsValid(this->GeneratedClass) || !IsValid(this->GeneratedClass->ClassDefaultObject))
	{
		return nullptr;
	}
	UAdventureCharacter* CharacterInstance = Cast<UAdventureCharacter>(this->GeneratedClass->ClassDefaultObject);
	if (!IsValid(CharacterInstance))
	{
		return nullptr;
	}
	return CharacterInstance->Icon;
}

UAdventureCharacter * UAdventureCharacterBlueprint::GetItemInstance(UAdventurePluginGameContext* GameContext)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("AdventureCharacterBlueprint:GetItemInstance")) || !IsValid(this->GeneratedClass))
	{
		return nullptr;
	}
	TSubclassOf<UAdventureCharacter> CharacterClass = (TSubclassOf<UAdventureCharacter>)(this->GeneratedClass);
	
	return GameContext->AdventureCharacterManager->GetCharacter(CharacterClass);
}
#pragma optimize("", on)