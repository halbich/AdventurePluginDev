#include "AdventureCharacterBlueprint.h"
#include "AdventureCharacter.h"

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
