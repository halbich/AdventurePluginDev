#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphEvent.generated.h"

/**
* Identifies a quest event.
*/
USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphEvent
{
	GENERATED_USTRUCT_BODY()

public:

	/**
	* The quest on which the represented quest is defined.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphEvent")
	UQuestGraph* Quest;

	/**
	* The name of the represented event.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphEvent")
	FName EventName;
};