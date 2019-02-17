#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphFlag.generated.h"

/**
* Identifies a quest flag.
*/
USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphFlag
{
	GENERATED_USTRUCT_BODY()

public:
	/**
	* The quest on which the represented flag is defined.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphFlag")
	UQuestGraph* Quest;
	/**
	* The name of the represented flag.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphFlag")
	FName FlagName;
};