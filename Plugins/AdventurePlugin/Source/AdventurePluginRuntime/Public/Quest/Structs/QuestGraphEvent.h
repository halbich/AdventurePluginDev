#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphEvent.generated.h"

USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphEvent
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphEvent")
	UQuestGraph* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphEvent")
	FName EventName;
};