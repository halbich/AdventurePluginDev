#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphString.generated.h"

USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphString
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphString")
	UQuestGraph* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphString")
	FName StringName;
};