#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphBool.generated.h"

/**
* Identifies a boolean quest variable.
*/
USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphBool
{
	GENERATED_USTRUCT_BODY()

public:

	/**
	* The quest on which the represented variable is defined.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphBool")
	UQuestGraph* Quest;

	/**
	* The name of the represented variable.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphBool")
	FName BoolName;
};