// Fill out your copyright notice in the Description page of Project Settings.

#include "BlueprintLibrary/AdventurePluginBlueprintLibrary.h"
#include "DialogGraph/DialogGraphNode.h"


#pragma optimize("", off)
void UAdventurePluginBlueprintLibrary::ShowDialog(UObject* WorldContextObject, UDialogGraph* graph)
{
	if (WorldContextObject->GetWorld() != nullptr)
	{
		auto instance = WorldContextObject->GetWorld()->GetGameInstance();
		if (instance != nullptr)
		{
			auto gameInstance = Cast<UAdventurePluginGameInstance>(instance);

			if (gameInstance != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Has proper Instance."));

				for (auto i : graph->AllNodes)
				{
					auto dn = Cast<UDialogGraphNode>(i);
					if (dn)
					{
						print(dn->DialogText.ToString());
					}
					else
						printR(TEXT("Node is not type of DialogGraphNOde"));
				}
			}

		}
	}
}


#pragma optimize("", on)

