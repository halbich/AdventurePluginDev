#pragma once
#include "Interface.h"
#include "DialogNodeShowOptionsCallbackInterface.generated.h"
class UDialogController;
/**
* @see IDialogNodeShowOptionsCallbackInterface
*/
UINTERFACE(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogNodeShowOptionsCallbackInterface : public UInterface
{
	GENERATED_BODY()
};
/**
* A node implementing this interface can respond when the user selects a dialog option.
*/
class IDialogNodeShowOptionsCallbackInterface
{
	GENERATED_BODY()

public:
	/**
	* Called when the user sellects a dialog option.
	* @param SelectedNodeIndex The option which the user selected.
	* @param DialogController The controller that initiated this call.
	* @return True if the execution should continue, i.e. the node was waiting for this callback, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Adventure Plugin|Dialog")
		bool DialogOptionSelected(int32 SelectedNodeIndex, UDialogController* DialogController);
};
