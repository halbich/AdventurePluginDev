// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UniquePtr.h"
#include "DialoguePresenterInterface.generated.h"

class UDialogGraphNode;
class UDialogueController;

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
		void ShowDialogueLine(UDialogGraphNode* node, UDialogueController* controller);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialogue")
		void ShowDialogueSelection(UPARAM(ref) TArray<UDialogGraphNode*>& options, UDialogueController* controller);
};
