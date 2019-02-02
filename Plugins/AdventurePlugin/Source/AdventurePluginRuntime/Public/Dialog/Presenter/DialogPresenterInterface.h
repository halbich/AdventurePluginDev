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
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialog")
		void SetPresenterVisibility(bool visible);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialog")
		void ShowDialogLine(FDialogLineData lineData, UDialogController* controller);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialog")
		void ShowDialogSelection(UPARAM(ref) TArray<FDialogLineData>& options, UDialogController* controller);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialog")
		void PlayAnimationOnce(const TScriptInterface<IAnimatableObjectInterface>& Target, FName AnimationName, UDialogController* Controller);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialog")
		void SetAnimationState(const TScriptInterface<IAnimatableObjectInterface>& Target, FName AnimationName);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialog")
		void ResetAnimationState(const TScriptInterface<IAnimatableObjectInterface>& Target);
};
