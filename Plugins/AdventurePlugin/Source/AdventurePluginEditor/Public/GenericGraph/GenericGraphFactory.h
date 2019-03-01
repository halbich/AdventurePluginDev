/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "GenericGraphFactory.generated.h"

/**
* A Factory class responsible for creating and importing new objects of type UGenericGraph.
* It is a base class for UDialogGraphFactory and UQuestGraphFactory.
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UGenericGraphFactory : public UFactory
{
	GENERATED_BODY()

public:
	UGenericGraphFactory();
	virtual ~UGenericGraphFactory();

	/**
	* Creates a new object of given type.
	* @param InClass
	* @param InParent
	* @param InName
	* @param Flags
	* @param Context
	* @param Warn
	* @return Newly created object.
	*/
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
