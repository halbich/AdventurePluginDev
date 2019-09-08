#pragma once

#include "CoreMinimal.h"
#include "Quest/Graph/QuestGraph.h"
#include "QuestGraphBool.generated.h"

/**
* Identifies a boolean quest variable.
* It is a pair of UQuestGraph and FName representing name of a boolean variable in the quest.
*/
USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphBool
{
	GENERATED_USTRUCT_BODY()

public:

	/**
	* UQuestGraph representing the quest on which the variable is defined.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphBool")
	UQuestGraph* Quest;

	/**
	* The name of the represented variable.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphBool")
	FName BoolName;
};