#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "InteractableSceneObjectFactory.generated.h"

/**
* Factory for creating blueprints for interactable objects.
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UInteractableSceneObjectFactory : public UFactory
{
	GENERATED_BODY()

public:

	UInteractableSceneObjectFactory();
	virtual ~UInteractableSceneObjectFactory() { }

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

protected:

	virtual bool IsMacroFactory() const { return false; }
};