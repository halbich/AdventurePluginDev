// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialoguePresenterInterface.generated.h"

class UDialogGraphNode;

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
	UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue")
		void ShowDialogueLine(UDialogGraphNode* node);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialogue")
		void ShowDialogueSelection(UDialogGraphNode* node);
};