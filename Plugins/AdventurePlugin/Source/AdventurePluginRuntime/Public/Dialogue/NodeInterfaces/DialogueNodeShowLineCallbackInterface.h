#pragma once
#include "Interface.h"
#include "DialogueNodeShowLineCallbackInterface.generated.h"
class UDialogueController;

UINTERFACE(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogueNodeShowLineCallbackInterface : public UInterface
{
	GENERATED_BODY()
};

class IDialogueNodeShowLineCallbackInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialogue")
		bool ShowDialogueLineCallback(UDialogueController* controller);
};
