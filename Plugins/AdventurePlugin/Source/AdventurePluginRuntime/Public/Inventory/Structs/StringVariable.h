#pragma once

#include "CoreMinimal.h"
#include "StringVariable.generated.h"


/**
* Data about a string variable that can be added to a quest.
*/
USTRUCT()
struct ADVENTUREPLUGINRUNTIME_API FStringVariable
{
	GENERATED_BODY()

public:
	/**
	* The default value of this variable.
	*/
	UPROPERTY(EditAnywhere)
		FString DefaultValue;
};