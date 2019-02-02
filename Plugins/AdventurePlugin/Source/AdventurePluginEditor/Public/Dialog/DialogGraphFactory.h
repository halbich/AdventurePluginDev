#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraphFactory.h"
#include "DialogGraphFactory.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UDialogGraphFactory : public UGenericGraphFactory
{
	GENERATED_BODY()

public:
	UDialogGraphFactory();
	virtual ~UDialogGraphFactory();
};
