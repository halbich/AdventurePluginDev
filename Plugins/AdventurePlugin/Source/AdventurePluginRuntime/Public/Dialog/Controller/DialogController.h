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

	void ShowDialog(UAdventurePluginGameContext* GameContext, UDialogGraph* DialogGraph);

	void ShowDialog(UAdventurePluginGameContext* GameContext, UDialogGraph* DialogGraph, UDialogGraphNode* StartNode);

	void HideDialog();

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Dialog")
		void ShowDialogLineCallback();

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Dialog")
		void ShowDialogLineSelectionCallback(int32 SelectedOptionIndex);

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Dialog")
		void PlayAnimationCallback(FName AnimationName, bool bSuccess);

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Adventure Plugin|Dialog")
		UDialogGraph* CurrentGraph;

	UPROPERTY(Transient)
		UAdventurePluginGameContext* CurrentGameContext;

private:

	UPROPERTY(Transient)
		UDialogGraphNode* CurrentNode;

	void BeginExecute(UDialogGraphNode* StartNode);

	FORCEINLINE IDialogPresenterInterface* GetPresenter()
	{
		return CurrentGameContext ? Cast<IDialogPresenterInterface>(CurrentGameContext->DialogPresenter.GetObject()) : nullptr;
	}
	/*How many steps since BeginExecute was last called.*/
	uint32 CurrentExecutionSteps;

	/*A fallback for infinite cycles - if the dialog execution takes more than this amount of steps, we'll assume we are in an infinite cycle.*/
	static const uint32 MaxExecutionSteps = 100000;
};
