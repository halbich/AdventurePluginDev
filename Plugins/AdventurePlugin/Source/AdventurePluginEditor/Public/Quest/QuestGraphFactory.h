#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraphFactory.h"
#include "QuestGraphFactory.generated.h"

/**
* A Factory class responsible for creating and importing new objects of type UQuestGraph
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UQuestGraphFactory : public UGenericGraphFactory
{
	GENERATED_BODY()

public:
	UQuestGraphFactory();
	virtual ~UQuestGraphFactory();
};
