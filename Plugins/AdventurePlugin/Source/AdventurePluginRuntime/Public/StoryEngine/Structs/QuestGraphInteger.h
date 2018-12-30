#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphInteger.generated.h"

USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphInteger
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphInteger")
	UQuestGraph* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphInteger")
	FName IntegerName;
};