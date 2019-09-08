#pragma once

#include "CoreMinimal.h"
#include "DialogNodePlayAnimationCallbackInterface.generated.h"

UINTERFACE(Blueprintable)

/**
* @see IDialogNodePlayAnimationCallbackInterface
*/
class ADVENTUREPLUGINRUNTIME_API UDialogNodePlayAnimationCallbackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
* A node implementing this interface can respond when an animation finishes on an object.
*/
class IDialogNodePlayAnimationCallbackInterface
{
	GENERATED_BODY()

public:

	/**
	* Called when an animation finishes.
	* @param AnimationName Which animation has finished.
	* @param Success True if the animation completed successfully.
	* @return True if the execution should continue, i.e. the node was waiting for this callback, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Adventure Plugin|Animations")
	bool PlayAnimationCallback(FName AnimationName, bool Success);
};
