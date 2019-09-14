#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "InventoryItemFactory.generated.h"

/**
* Factory for creating blueprints for inventory items. Makes sure that when the user
* want to create UInventoryItem asset, it will create UInventoryItemBlueprint instead.
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UInventoryItemFactory : public UFactory
{
	GENERATED_BODY()

public:

	UInventoryItemFactory();
	virtual ~UInventoryItemFactory() { }

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

protected:

	virtual bool IsMacroFactory() const { return false; }
};