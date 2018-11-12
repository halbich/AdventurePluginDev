// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Graph/DialogGraphNode.h"
#include "DialoguePresenterInterface.h"
#include "DialoguePresenterWidget.generated.h"

/**
 *
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UDialoguePresenterWidget : public UUserWidget, public IDialoguePresenterInterface
{
	GENERATED_BODY()

public:
	void SetPresenterVisibility(bool visible);

	void ShowDialogueLine(FDialogLineData lineData, UDialogueController* controller);

	void ShowDialogueSelection(TArray<FDialogLineData>& options, UDialogueController* controller);
};
