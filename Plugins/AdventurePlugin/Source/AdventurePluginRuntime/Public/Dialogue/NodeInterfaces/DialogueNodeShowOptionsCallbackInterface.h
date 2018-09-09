#pragma once
#include "Interface.h"
#include "DialogueNodeShowOptionsCallbackInterface.generated.h"
class UDialogueController;

UINTERFACE(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogueNodeShowOptionsCallbackInterface : public UInterface
{
	GENERATED_BODY()
};

class IDialogueNodeShowOptionsCallbackInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialogue")
		bool DialogueOptionSelected(int32 selectedNodeIndex, UDialogueController* controller);
};
