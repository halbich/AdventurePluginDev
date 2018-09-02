// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Graph/DialogGraphNode.h"
#include "DialoguePresenterWidget.generated.h"

/**
 *
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UDialoguePresenterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue")
		void ShowDialogueLine(UDialogGraphNode* node);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialogue")
		void ShowDialogueSelection(UDialogGraphNode* node);
};
