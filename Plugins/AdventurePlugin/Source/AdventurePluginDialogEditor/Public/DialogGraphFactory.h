#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraphFactory.h"
#include "DialogGraphFactory.generated.h"

/**
* A Factory class responsible for creating and importing new objects of type UDialogGraph
*/
UCLASS()
class ADVENTUREPLUGINDIALOGEDITOR_API UDialogGraphFactory : public UGenericGraphFactory
{
	GENERATED_BODY()

public:
	UDialogGraphFactory();
	virtual ~UDialogGraphFactory();
};
