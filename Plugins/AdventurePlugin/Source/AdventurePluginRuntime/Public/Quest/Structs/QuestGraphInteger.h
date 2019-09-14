#pragma once

#include "CoreMinimal.h"
#include "Quest/Graph/QuestGraph.h"
#include "QuestGraphInteger.generated.h"

/**
* Identifies an integer quest variable.
* It is a pair of UQuestGraph and FName representing name of an integer variable in the quest.
*/
USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphInteger
{
	GENERATED_USTRUCT_BODY()

public:

	/**
	* UQuestGraph representing the quest on which the variable is defined.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphInteger")
	UQuestGraph* Quest;

	/**
	* The name of the represented variable.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphInteger")
	FName IntegerName;
};