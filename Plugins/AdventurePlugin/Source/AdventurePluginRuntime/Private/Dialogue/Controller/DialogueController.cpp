// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueController.h"




void UDialogueController::ShowDialog(UDialogGraph* graph, UGameInstance* instance)
{
	if (!presenterInstance || !presenterInstance->IsValidLowLevel())
	{
		auto cdo = DefaultPresenter.Get();
		if (cdo)
			presenterInstance = CreateWidget<UDialoguePresenterWidget>(instance, cdo);

		if (!presenterInstance || !presenterInstance->IsValidLowLevel())
			setDefaulPresenterInstance(instance);

		if (!presenterInstance || !presenterInstance->IsValidLowLevel())
		{
			// TODO log error
			return;
		}

	}

	// TODo get player index
	presenterInstance->AddToViewport(0);
}