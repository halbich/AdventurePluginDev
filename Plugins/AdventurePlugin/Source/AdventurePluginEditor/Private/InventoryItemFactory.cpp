#include "InventoryItemFactory.h"
#include "Inventory/InventoryItem.h"

UInventoryItemFactory::UInventoryItemFactory(/*const class FObjectInitializer &OBJ*/)// : Super(OBJ)
{
	bEditAfterNew = true;
	bCreateNew = true;
	SupportedClass = UInventoryItem::StaticClass();
}

UObject* UInventoryItemFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(Class->IsChildOf(UInventoryItem::StaticClass()));
	return NewObject<UInventoryItem>(InParent, Class, Name, Flags | RF_Transactional, Context);
}