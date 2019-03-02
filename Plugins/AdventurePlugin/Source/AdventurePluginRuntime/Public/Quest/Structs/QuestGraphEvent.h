#pragma once

#include "CoreMinimal.h"
#include "QuestGraph.h"
#include "QuestGraphEvent.generated.h"

/**
* Identifies a quest event.
* It is a pair of UQuestGraph and FName representing name of an event in the quest.
*/
USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FQuestGraphEvent
{
	GENERATED_USTRUCT_BODY()

public:

	/**
	* UQuestGraph representing the quest on which the event is defined.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphEvent")
	UQuestGraph* Quest;

	/**
	* The name of the represented event.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphEvent")
	FName EventName;
};