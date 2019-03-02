#pragma once

#include "CoreMinimal.h"
#include "IntegerVariable.generated.h"

/**
* Simple struct representing definition of an integer variable in a quest.
* @see UQuestGraph
*/
USTRUCT()
struct ADVENTUREPLUGINRUNTIME_API FIntegerVariable
{
	GENERATED_BODY()

public:

	/**
	* The default value of this variable. It is used when the value
	* of this variable is read from the quest without writing to it first.
	*/
	UPROPERTY(EditAnywhere)
	int32 DefaultValue;
};