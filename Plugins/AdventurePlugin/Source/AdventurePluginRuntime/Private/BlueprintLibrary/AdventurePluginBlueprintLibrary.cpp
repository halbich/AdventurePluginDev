// Fill out your copyright notice in the Description page of Project Settings.

#include "BlueprintLibrary/AdventurePluginBlueprintLibrary.h"

#pragma optimize("", off)
void UAdventurePluginBlueprintLibrary::ShowDialog(UObject* WorldContextObject, UDialogGraph* graph)
{
	// TODO error messages

	if (!WorldContextObject)
		return;

	auto world = WorldContextObject->GetWorld();
	if (!world)
		return;

	auto instance = Cast<UAdventurePluginGameInstance>(world->GetGameInstance());
	if (!instance)
		return;

	instance->ShowDialog(graph);

	
}

#pragma optimize("", on)