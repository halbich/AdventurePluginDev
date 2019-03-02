#pragma once

#include "CoreMinimal.h"
#include "BoolVariable.generated.h"

/**
* Simple struct representing definition of a boolean variable in a quest.
* @see UQuestGraph
*/
USTRUCT()
struct ADVENTUREPLUGINRUNTIME_API FBoolVariable
{
	GENERATED_BODY()

public:

	/**
	* The default value of this variable. It is used when the value
	* of this variable is read from the quest without writing to it first.
	*/
	UPROPERTY(EditAnywhere)
	bool DefaultValue;
};