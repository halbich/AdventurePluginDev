#pragma once

#include "CoreMinimal.h"
#include "GenericGraphRuntime/Public/GenericGraph.h"
#include "QuestGraph.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UQuestGraph : public UGenericGraph
{
	GENERATED_BODY()

public:
	UQuestGraph();
	virtual ~UQuestGraph();
};
