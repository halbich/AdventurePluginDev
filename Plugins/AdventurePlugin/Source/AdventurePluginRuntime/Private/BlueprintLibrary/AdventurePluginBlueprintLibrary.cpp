// Fill out your copyright notice in the Description page of Project Settings.

#include "BlueprintLibrary/AdventurePluginBlueprintLibrary.h"


#pragma optimize("", off)
void UAdventurePluginBlueprintLibrary::ShowDialog(UObject* WorldContextObject)
{
	if (WorldContextObject->GetWorld() != nullptr)
	{
		auto instance = WorldContextObject->GetWorld()->GetGameInstance();
		if (instance != nullptr)
		{
			auto gameInstance = Cast<UAdventurePluginGameInstance>(instance);

			if (gameInstance != nullptr)
			{


			}
			
		}
	}
}


#pragma optimize("", on)

