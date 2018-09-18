#pragma once

#include "Core.h"
#include "Factories/Factory.h"
#include "InventoryItemFactory.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UInventoryItemFactory : public UFactory
{
	GENERATED_BODY()

public:

	UInventoryItemFactory();
	virtual ~UInventoryItemFactory() { }

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

protected:

	virtual bool IsMacroFactory() const { return false; }
};