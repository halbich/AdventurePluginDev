#pragma once

#include "CoreMinimal.h"
#include "IntegerVariable.generated.h"

/**
* Data about an integer variable that can be added to a quest.
*/
USTRUCT()
struct ADVENTUREPLUGINRUNTIME_API FIntegerVariable
{
	GENERATED_BODY()

public:

	/**
	* The default value of this variable.
	*/
	UPROPERTY(EditAnywhere)
	int32 DefaultValue;
};