// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginGameInstance.h"

#pragma optimize("", off)
void UAdventurePluginGameInstance::ShowDialog(UDialogGraph* graph, UDialogueController* overrideController)
{
	if (currentDialogueInstance)
	{
		// TODO report error, should be cleared
	}

	currentDialogueInstance = overrideController != nullptr ? overrideController : getDefaultDialogueInstance();

	if (!currentDialogueInstance || !currentDialogueInstance->IsValidLowLevel())
	{
		// TODO report error, should be valid
		return;
	}

	if (currentDialogueInstance != defaultDialogueInstance)
	{
		// TODO hook on events
	}

	currentDialogueInstance->ShowDialog(graph, this);
}

#pragma optimize("", on)