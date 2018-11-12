// Fill out your copyright notice in the Description page of Project Settings.

#include "APDevBPLibrary.h"




UAdventurePluginGameContext* UAPDevBPLibrary::GetCurrentGameContext(UObject* worldObjectContext)
{
	auto instance = Cast<UAPDevGameInstance>(UGameplayStatics::GetGameInstance(worldObjectContext));
	return instance->CurrentGameContext;
}