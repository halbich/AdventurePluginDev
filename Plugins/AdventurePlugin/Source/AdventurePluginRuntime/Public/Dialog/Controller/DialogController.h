// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AdventurePluginRuntime.h"
#include "Common/AdventurePluginGameContext.h"
#include "Common/AdventurePluginConfig.h"
#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "Presenter/DialogPresenterInterface.h"
#include "Kismet/GameplayStatics.h"
#include "DialogController.generated.h"


/**
 *
 */
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogController : public UObject
{
	GENERATED_BODY()

public:

	void ShowDialog(UAdventurePluginGameContext* gameContext, UDialogGraph* graph);

	void ShowDialog(UAdventurePluginGameContext* gameContext, UDialogGraph* graph, UDialogGraphNode* startNode);

	void HideDialog();

	UFUNCTION(BlueprintCallable, Category = "Dialog")
		void ShowDialogLineCallback();

	UFUNCTION(BlueprintCallable, Category = "Dialog")
		void ShowDialogLineSelectionCallback(int32 selectedOptionIndex);

	UFUNCTION(BlueprintCallable, Category = "Dialog")
		void PlayAnimationCallback(FName AnimationName, bool Success);

	UPROPERTY(BlueprintReadOnly, Transient)
		UDialogGraph* CurrentGraph;

	UPROPERTY(Transient)
		UAdventurePluginGameContext* currentContext;

private:

	UPROPERTY(Transient)
		UDialogGraphNode* currentNode;

	void beginExecute(UDialogGraphNode* node);

	FORCEINLINE IDialogPresenterInterface* presenter()
	{
		return currentContext ? Cast<IDialogPresenterInterface>(currentContext->DialogPresenter.GetObject()) : NULL;
	}
};
