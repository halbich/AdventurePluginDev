// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UniquePtr.h"
#include "Structs/DialogLineData.h"
#include "DialogPresenterInterface.generated.h"

class UDialogGraphNode;
class UDialogController;
class IAnimatableObjectInterface;

/**
 *
 */
UINTERFACE(BlueprintType)
class ADVENTUREPLUGINRUNTIME_API UDialogPresenterInterface : public UInterface
{
	GENERATED_BODY()


};

class IDialogPresenterInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Dialog")
		void SetPresenterVisibility(bool bVisible);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Dialog")
		void ShowDialogLine(FDialogLineData DialogLineData, UDialogController* DialogController);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Dialog")
		void ShowDialogSelection(UPARAM(ref) TArray<FDialogLineData>& Options, UDialogController* DialogController);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Dialog")
		void PlayAnimationOnce(const TScriptInterface<IAnimatableObjectInterface>& AnimationTarget, FName AnimationName, UDialogController* DialogController);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Dialog")
		void SetAnimationState(const TScriptInterface<IAnimatableObjectInterface>& AnimationTarget, FName AnimationName);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Adventure Plugin|Dialog")
		void ResetAnimationState(const TScriptInterface<IAnimatableObjectInterface>& AnimationTarget);
};
