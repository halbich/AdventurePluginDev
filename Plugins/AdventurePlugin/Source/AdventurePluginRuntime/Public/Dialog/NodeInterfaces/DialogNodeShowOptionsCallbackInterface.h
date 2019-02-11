#pragma once
#include "Interface.h"
#include "DialogNodeShowOptionsCallbackInterface.generated.h"
class UDialogController;

UINTERFACE(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogNodeShowOptionsCallbackInterface : public UInterface
{
	GENERATED_BODY()
};

class IDialogNodeShowOptionsCallbackInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Adventure Plugin|Dialog")
		bool DialogOptionSelected(int32 SelectedNodeIndex, UDialogController* DialogController);
};
