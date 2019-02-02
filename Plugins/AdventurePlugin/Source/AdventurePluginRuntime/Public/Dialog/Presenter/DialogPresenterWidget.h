// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Graph/DialogGraphNode.h"
#include "DialogPresenterInterface.h"
#include "DialogPresenterWidget.generated.h"

/**
 *
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UDialogPresenterWidget : public UUserWidget, public IDialogPresenterInterface
{
	GENERATED_BODY()

public:
	void SetPresenterVisibility(bool visible);

	void ShowDialogLine(FDialogLineData lineData, UDialogController* controller);

	void ShowDialogSelection(TArray<FDialogLineData>& options, UDialogController* controller);

	void PlayAnimationOnce(const TScriptInterface<IAnimatableObjectInterface>& Target, FName AnimationName, UDialogController* Controller);

	void SetAnimationState(const TScriptInterface<IAnimatableObjectInterface>& Target, FName AnimationName);
	
	void ResetAnimationState(const TScriptInterface<IAnimatableObjectInterface>& Target);
};
