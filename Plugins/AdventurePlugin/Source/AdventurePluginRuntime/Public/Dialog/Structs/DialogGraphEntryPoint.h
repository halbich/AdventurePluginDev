#pragma once

#include "CoreMinimal.h"
#include "Dialog/Graph/DialogGraph.h"
#include "DialogGraphEntryPoint.generated.h"

/**
* Specifies a point where a dialog can start.
*/
USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FDialogGraphEntryPoint
{
	GENERATED_USTRUCT_BODY()

public:

	/**
	* The dialog that should be played.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphEntryPoint")
	UDialogGraph* Dialog;

	/**
	* The entry point where the execution should start.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphEntryPoint")
	FName EntryPointName;
};