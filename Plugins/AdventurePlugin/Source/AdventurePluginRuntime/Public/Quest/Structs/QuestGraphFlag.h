#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphFlag.generated.h"

/**
* Identifies a quest flag.
* It is a pair of UQuestGraph and FName representing name of a flag in the quest.
*/
USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphFlag
{
	GENERATED_USTRUCT_BODY()

public:

	/**
	* UQuestGraph representing the quest on which the flag is defined.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphFlag")
	UQuestGraph* Quest;

	/**
	* The name of the represented flag.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphFlag")
	FName FlagName;
};