// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "Presenter/DialoguePresenterInterface.h"
#include "Common/AdventurePluginConfig.h"
#include "Kismet/GameplayStatics.h"
#include "AdventurePluginGameContext.h"
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

	UFUNCTION(BlueprintCallable, Category = "Dialogue", meta = (WorldContext = "WorldContextObject"))
		void ShowDialogLineCallback(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Dialogue", meta = (WorldContext = "WorldContextObject"))
		void ShowDialogLineSelectionCallback(UObject* WorldContextObject, int32 selectedOptionIndex);

	UPROPERTY(BlueprintReadOnly, Transient)
		UDialogGraph* CurrentGraph;

private:
	UPROPERTY(Transient)
		TScriptInterface<IDialoguePresenterInterface> currentPresenter;

	UPROPERTY(Transient)
		UAdventurePluginGameContext* currentContext;

	UPROPERTY(Transient)
		UDialogGraphNode* currentNode;

	void beginExecute(UDialogGraphNode* node);

	FORCEINLINE IDialoguePresenterInterface* presenter()
	{
		return Cast<IDialoguePresenterInterface>(currentContext->DialoguePresenter.GetObject());
	}
};
