#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphInteger.generated.h"

/**
* Identifies an integer quest variable.
*/
USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphInteger
{
	GENERATED_USTRUCT_BODY()

public:

	/**
	* The quest on which the represented variable is defined.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphInteger")
	UQuestGraph* Quest;

	/**
	* The name of the represented variable.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphInteger")
	FName IntegerName;
};