#include "InventoryItemFactory.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Inventory/InventoryItem.h"
#include "Inventory/InventoryItemBlueprint.h"

UInventoryItemFactory::UInventoryItemFactory()
{
	bEditAfterNew = true;
	bCreateNew = true;
	SupportedClass = UInventoryItem::StaticClass();
}

UObject* UInventoryItemFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	check(Class->IsChildOf(UInventoryItem::StaticClass()));
	if (!FKismetEditorUtilities::CanCreateBlueprintOfClass(UInventoryItem::StaticClass()))
	{
		FFormatNamedArguments Args;
		FMessageDialog::Open(EAppMsgType::Ok, NSLOCTEXT("UInventoryItemFactory", "CannotCreateInventoryItem", "Cannot create inventory item blueprint."));
		return nullptr;
	}
	else
	{
		return FKismetEditorUtilities::CreateBlueprint(UInventoryItem::StaticClass(), InParent, Name, EBlueprintType::BPTYPE_Normal, UInventoryItemBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), CallingContext);
	}
}

UObject* UInventoryItemFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, NAME_None);
}