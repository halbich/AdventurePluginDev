#pragma once

#include "CoreMinimal.h"
#include "UseActionType.generated.h"

USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FUseActionType
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UseActionType")
	FName UseActionTypeName;
};