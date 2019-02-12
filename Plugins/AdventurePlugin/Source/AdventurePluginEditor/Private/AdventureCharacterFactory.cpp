#include "AdventureCharacterFactory.h"
#include "AdventureCharacter.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "AdventureCharacterBlueprint.h"

UAdventureCharacterFactory::UAdventureCharacterFactory(/*const class FObjectInitializer &OBJ*/)// : Super(OBJ)
{
	bEditAfterNew = true;
	bCreateNew = true;
	SupportedClass = UAdventureCharacter::StaticClass();
}

UObject* UAdventureCharacterFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	check(Class->IsChildOf(UAdventureCharacter::StaticClass()));
	if (!FKismetEditorUtilities::CanCreateBlueprintOfClass(UAdventureCharacter::StaticClass()))
	{
		FFormatNamedArguments Args;
		FMessageDialog::Open(EAppMsgType::Ok, NSLOCTEXT("UAdventureCharacterFactory", "CannotCreateAdventureCharacter", "Cannot create character blueprint."));
		return nullptr;
	}
	else
	{
		return FKismetEditorUtilities::CreateBlueprint(UAdventureCharacter::StaticClass(), InParent, Name, EBlueprintType::BPTYPE_Normal, UAdventureCharacterBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), CallingContext);
	}
}

UObject* UAdventureCharacterFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, NAME_None);
}