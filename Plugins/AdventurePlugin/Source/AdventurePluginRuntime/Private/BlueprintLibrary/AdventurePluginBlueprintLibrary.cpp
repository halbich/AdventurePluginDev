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


	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Has proper Instance."));

	for (auto i : graph->AllNodes)
	{
		auto dn = Cast<UDialogGraphNode>(i);
		if (dn)
		{
			print(dn->DialogText.ToString());

			for (auto children : dn->ChildrenNodes)
			{
				auto childrenDN = Cast<UDialogGraphNode>(children);
				if (childrenDN)
				{
					print(TEXT("Found children!"));
					print(childrenDN->DialogText.ToString());
				}
			}

		}
		else
			printR(TEXT("Node is not type of DialogGraphNOde"));
	}

}


#pragma optimize("", on)

