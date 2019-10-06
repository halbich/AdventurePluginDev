#pragma once

#include "CoreMinimal.h"
#include "DialogGraphEntryPoint.generated.h"

class UDialogGraph;

/**
* Specifies the entry point where a dialog can start.
* It is a pair of UDialogGraph and FName representing entry point name in that graph.
*/
USTRUCT(BlueprintType)
struct ADVENTUREPLUGINRUNTIME_API FDialogGraphEntryPoint
{
	GENERATED_USTRUCT_BODY()

public:

	/**
	* UDialogGraph representing the dialog that should be played.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphEntryPoint")
	UDialogGraph* Dialog;

	/**
	* The entry point name where the execution of this dialog should start.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphEntryPoint")
	FName EntryPointName;
};