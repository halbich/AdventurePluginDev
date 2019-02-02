#pragma once
#include "Interface.h"
#include "DialogNodePlayAnimationCallbackInterface.generated.h"

UINTERFACE(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogNodePlayAnimationCallbackInterface : public UInterface
{
	GENERATED_BODY()
};

class IDialogNodePlayAnimationCallbackInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialog|Animations")
		bool PlayAnimationCallback(FName AnimationName, bool Success);
};
