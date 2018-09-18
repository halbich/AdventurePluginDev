#include "AdventureCharacterFactory.h"
#include "AdventureCharacter.h"

UAdventureCharacterFactory::UAdventureCharacterFactory(/*const class FObjectInitializer &OBJ*/)// : Super(OBJ)
{
	bEditAfterNew = true;
	bCreateNew = true;
	SupportedClass = UAdventureCharacter::StaticClass();
}

UObject* UAdventureCharacterFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(Class->IsChildOf(UAdventureCharacter::StaticClass()));
	return NewObject<UAdventureCharacter>(InParent, Class, Name, Flags | RF_Transactional, Context);
}