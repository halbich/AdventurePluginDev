// Fill out your copyright notice in the Description page of Project Settings.

#include "APDevBPLibrary.h"




UAdventurePluginGameContext* UAPDevBPLibrary::GetCurrentGameContext(UObject* WorldObjectContext)
{
	UAPDevGameInstance* GameInstance = Cast<UAPDevGameInstance>(UGameplayStatics::GetGameInstance(WorldObjectContext));
	return GameInstance->CurrentGameContext;
}