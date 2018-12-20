#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphFlag.generated.h"

USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphFlag
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphFlag")
	UQuestGraph* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphFlag")
	FName FlagName;
};