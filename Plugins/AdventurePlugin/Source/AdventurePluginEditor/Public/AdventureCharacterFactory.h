#pragma once

#include "Core.h"
#include "Factories/Factory.h"
#include "AdventureCharacterFactory.generated.h"

/**
* Factory for creating blueprints for adventure characters..
* Makes sure that when the user creates a blueprint for UAdventureCharacter, she will create UInventoryItemBlueprint.
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UAdventureCharacterFactory : public UFactory
{
	GENERATED_BODY()

public:

	UAdventureCharacterFactory();
	virtual ~UAdventureCharacterFactory() { }

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

protected:

	virtual bool IsMacroFactory() const { return false; }
};