#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphString.generated.h"

/**
* Identifies a string quest variable.
*/
USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphString
{
	GENERATED_USTRUCT_BODY()

public:

	/**
	* The quest on which the represented variable is defined.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphString")
	UQuestGraph* Quest;

	/**
	* The name of the represented variable.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphString")
	FName StringName;
};