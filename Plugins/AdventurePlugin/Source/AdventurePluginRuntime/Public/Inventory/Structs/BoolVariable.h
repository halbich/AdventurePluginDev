#pragma once

#include "CoreMinimal.h"
#include "BoolVariable.generated.h"
/**
* Data about a boolean variable that can be added to a quest.
*/
USTRUCT()
struct ADVENTUREPLUGINRUNTIME_API FBoolVariable
{
	GENERATED_BODY()

public:
	/**
	* The default value of this variable.
	*/
	UPROPERTY(EditAnywhere)
		bool DefaultValue;
};