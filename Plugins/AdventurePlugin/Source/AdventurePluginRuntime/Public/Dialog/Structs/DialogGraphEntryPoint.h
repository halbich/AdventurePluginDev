#pragma once

#include "CoreMinimal.h"
#include "Dialog/Graph/DialogGraph.h"
#include "DialogGraphEntryPoint.generated.h"

USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FDialogGraphEntryPoint
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphEntryPoint")
	UDialogGraph* Dialog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphEntryPoint")
	FName EntryPointName;
};