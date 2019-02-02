#pragma once
#include "Interface.h"
#include "DialogNodeShowLineCallbackInterface.generated.h"
class UDialogController;

UINTERFACE(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogNodeShowLineCallbackInterface : public UInterface
{
	GENERATED_BODY()
};

class IDialogNodeShowLineCallbackInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialog")
		bool ShowDialogLineCallback(UDialogController* controller);
};
