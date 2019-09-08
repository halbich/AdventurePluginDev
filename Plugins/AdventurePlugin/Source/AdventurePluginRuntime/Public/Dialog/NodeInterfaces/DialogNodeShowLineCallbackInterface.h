#pragma once

#include "CoreMinimal.h"
#include "DialogNodeShowLineCallbackInterface.generated.h"

class UDialogController;

/**
* @see IDialogNodeShowLineCallbackInterface
*/
UINTERFACE(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogNodeShowLineCallbackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
* A node implementing this interface can respond when a dialog line finishes.
*/
class IDialogNodeShowLineCallbackInterface
{
	GENERATED_BODY()

public:

	/**
	* Called when a Dialog line finishes.
	* @param DialogController Dialog controller which started the dialog line execution.
	* @return True if the execution should continue, i.e. the node was waiting for this callback, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Adventure Plugin|Dialog")
	bool ShowDialogLineCallback(UDialogController* DialogController);
};
