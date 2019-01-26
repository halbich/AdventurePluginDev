// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UniquePtr.h"
#include "Structs/DialogLineData.h"
#include "DialoguePresenterInterface.generated.h"

class UDialogGraphNode;
class UDialogueController;
class IAnimatableObjectInterface;

/**
 *
 */
UINTERFACE(BlueprintType)
class ADVENTUREPLUGINRUNTIME_API UDialoguePresenterInterface : public UInterface
{
	GENERATED_BODY()


};

class IDialoguePresenterInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialogue")
		void SetPresenterVisibility(bool visible);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialogue")
		void ShowDialogueLine(FDialogLineData lineData, UDialogueController* controller);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialogue")
		void ShowDialogueSelection(UPARAM(ref) TArray<FDialogLineData>& options, UDialogueController* controller);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialogue")
		void PlayAnimationOnce(const TScriptInterface<IAnimatableObjectInterface>& Target, FName AnimationName, UDialogueController* Controller);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialogue")
		void SetAnimationState(const TScriptInterface<IAnimatableObjectInterface>& Target, FName AnimationName);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialogue")
		void ResetAnimationState(const TScriptInterface<IAnimatableObjectInterface>& Target);
};
