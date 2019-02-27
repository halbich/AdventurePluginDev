/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "GenericGraphFactory.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UGenericGraphFactory : public UFactory
{
	GENERATED_BODY()

public:
	UGenericGraphFactory();
	virtual ~UGenericGraphFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
