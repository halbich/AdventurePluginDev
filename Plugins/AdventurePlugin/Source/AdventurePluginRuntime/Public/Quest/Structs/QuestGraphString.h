#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphString.generated.h"

/**
* Identifies a string quest variable.
* It is a pair of UQuestGraph and FName representing name of a string variable in the quest.
*/
USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphString
{
	GENERATED_USTRUCT_BODY()

public:

	/**
	* UQuestGraph representing the quest on which the variable is defined.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphString")
	UQuestGraph* Quest;

	/**
	* The name of the represented variable.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphString")
	FName StringName;
};