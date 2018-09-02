// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Graph/DialogGraph.h"
#include "Presenter/DialoguePresenterWidget.h"
#include "Config/AdventurePluginConfig.h"
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

	// TODO get rid of gameINstance
	void ShowDialog(UDialogGraph* graph, UGameInstance* instance);

	void HideDialog();

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
		TSubclassOf<UDialoguePresenterWidget> DefaultPresenter;

private:
	UPROPERTY(Transient)
		UDialoguePresenterWidget* presenterInstance;

	UPROPERTY(Transient)
		UGameInstance* cachedGameInstance;



	FORCEINLINE void setDefaulPresenterInstance(UGameInstance* gameInstance)
	{
		auto settings = GetMutableDefault<UAdventurePluginConfig>();

		if (settings->DefaultDialoguePresenterWidget.IsValid())
		{
			// we have C++ class
			auto inst = settings->DefaultDialoguePresenterWidget.Get();
			if (inst)
				presenterInstance = CreateWidget<UDialoguePresenterWidget>(gameInstance, inst);
		}
		else
		{
			// we have Blueprint class
			auto inst = settings->DefaultDialoguePresenterWidget.LoadSynchronous();
			if (inst)
				presenterInstance = CreateWidget<UDialoguePresenterWidget>(gameInstance, inst);
		}
	}

	void beginExecute(UDialogGraphNode* node);
};