#pragma once

#include "CoreMinimal.h"
#include "GenericGraphEditor/Private/GenericGraphFactory.h"
#include "QuestGraphFactory.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UQuestGraphFactory : public UGenericGraphFactory
{
	GENERATED_BODY()

public:
	UQuestGraphFactory();
	virtual ~UQuestGraphFactory();
};
