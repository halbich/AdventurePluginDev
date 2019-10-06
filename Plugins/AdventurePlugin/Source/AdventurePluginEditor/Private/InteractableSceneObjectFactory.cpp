#include "InteractableSceneObjectFactory.h"
#include "InteractableSceneObject.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Combinations/CombinableObjectBlueprint.h"

UInteractableSceneObjectFactory::UInteractableSceneObjectFactory()
{
	bEditAfterNew = true;
	bCreateNew = true;
	SupportedClass = UInteractableSceneObject::StaticClass();
}

UObject* UInteractableSceneObjectFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	check(Class->IsChildOf(UInteractableSceneObject::StaticClass()));
	if (!FKismetEditorUtilities::CanCreateBlueprintOfClass(UInteractableSceneObject::StaticClass()))
	{
		FFormatNamedArguments Args;
		FMessageDialog::Open(EAppMsgType::Ok, NSLOCTEXT("UInteractableSceneObjectFactory", "CannotCreateInteractableObject", "Cannot create interactable object."));
		return nullptr;
	}
	else
	{
		return FKismetEditorUtilities::CreateBlueprint(UInteractableSceneObject::StaticClass(), InParent, Name, EBlueprintType::BPTYPE_Normal, UCombinableObjectBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), CallingContext);
	}
}

UObject* UInteractableSceneObjectFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, NAME_None);
}