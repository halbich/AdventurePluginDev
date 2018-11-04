// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginBlueprintLibrary.h"

#pragma optimize("", off)
void UAdventurePluginBlueprintLibrary::ShowDialog(UAdventurePluginGameContext* gameContext, UDialogGraph* graph)
{
	// TODO error messages

	/*if (!WorldContextObject)
		return;

	auto world = WorldContextObject->GetWorld();
	if (!world)
		return;

	auto instance = Cast<UAdventurePluginGameInstance>(world->GetGameInstance());
	if (!instance)
		return;

	instance->ShowDialog(graph);*/

	
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