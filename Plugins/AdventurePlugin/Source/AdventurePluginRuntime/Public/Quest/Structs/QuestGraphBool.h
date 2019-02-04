#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphBool.generated.h"

USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphBool
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphBool")
	UQuestGraph* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphBool")
	FName BoolName;
};