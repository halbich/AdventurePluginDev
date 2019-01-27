// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AdventurePluginRuntime.h"
#include "Common/AdventurePluginGameContext.h"
#include "Common/AdventurePluginConfig.h"
#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "Presenter/DialoguePresenterInterface.h"
#include "Kismet/GameplayStatics.h"
#include "DialogueController.generated.h"


/**
 *
 */
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogueController : public UObject
{
	GENERATED_BODY()

public:

	void ShowDialog(UAdventurePluginGameContext* gameContext, UDialogGraph* graph);

	void ShowDialog(UAdventurePluginGameContext* gameContext, UDialogGraph* graph, UDialogGraphNode* startNode);

	void HideDialog();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		void ShowDialogLineCallback();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		void ShowDialogLineSelectionCallback(int32 selectedOptionIndex);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		void PlayAnimationCallback(FName AnimationName, bool Success);

	UPROPERTY(BlueprintReadOnly, Transient)
		UDialogGraph* CurrentGraph;

	UPROPERTY(Transient)
		UAdventurePluginGameContext* currentContext;

private:

	UPROPERTY(Transient)
		UDialogGraphNode* currentNode;

	void beginExecute(UDialogGraphNode* node);

	FORCEINLINE IDialoguePresenterInterface* presenter()
	{
		return currentContext ? Cast<IDialoguePresenterInterface>(currentContext->DialoguePresenter.GetObject()) : NULL;
	}
};
