#pragma once

#include "CoreMinimal.h"
#include "DialogPlayerOptionData.generated.h"

USTRUCT(BlueprintType)
struct FDialogPlayerOptionData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "DialogPlayerOptionData")
		FText OptionText;
};