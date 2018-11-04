// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginBlueprintLibrary.h"

#pragma optimize("", off)
void UAdventurePluginBlueprintLibrary::ShowDialog(UAdventurePluginGameContext* gameContext, UDialogGraph* graph)
{
	if (!gameContext || !gameContext->IsValidLowLevel())
	{
		LOG_Error(NSLOCTEXT("AP","GameContextNull","Show dialog::gameContext is NULL"));
		return;
	}

	if (!graph || !graph->IsValidLowLevel())
	{
		LOG_Warning(NSLOCTEXT("AP", "DialogGraphNull", "Show dialog::graph is NULL"));
		return;
	}

	auto dc = gameContext->DialogueController;
	if (!dc || !dc->IsValidLowLevel())
	{
		LOG_Warning(NSLOCTEXT("AP", "DialogControllerNull", "Show dialog::gameContext->DialogueController is NULL"));
		return;
	}

	dc->ShowDialog(gameContext, graph);

}

void UAdventurePluginBlueprintLibrary::ShowInventory(UAdventurePluginGameContext* gameContext, bool bShow)
{
	// TODO error messages

	/*if (!WorldContextObject) return;

	auto world = WorldContextObject->GetWorld();
	if (!world) return;

	auto instance = Cast<UAdventurePluginGameInstance>(world->GetGameInstance());
	if (!instance) return;

	instance->ShowInventory(bShow);*/
}

#pragma optimize("", on)