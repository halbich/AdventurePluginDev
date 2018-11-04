// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginGameContext.h"



void UAdventurePluginGameContext::InitFromConfig(UGameInstance* owningGame)
{
	auto settings = GetMutableDefault<UAdventurePluginConfig>();

	auto icInst = (settings->DefaultInventoryManager.IsValid())
		? settings->DefaultInventoryManager.Get()				// we have C++ class
		: settings->DefaultInventoryManager.LoadSynchronous();	// we have Blueprint class
	if (icInst)
		InventoryController = icInst->GetDefaultObject<UInventoryController>();

	auto ipInst = (settings->DefaultInventoryPresenterWidget.IsValid())
		? settings->DefaultInventoryPresenterWidget.Get()				// we have C++ class
		: settings->DefaultInventoryPresenterWidget.LoadSynchronous();	// we have Blueprint class
	if (ipInst) 
		InventoryPresenter = CreateWidget<UInventoryPresenterWidget>(owningGame, ipInst);



	auto dcInst = (settings->DefaultDialogueController.IsValid())
		? settings->DefaultDialogueController.Get()				// we have C++ class
		: settings->DefaultDialogueController.LoadSynchronous();	// we have Blueprint class
	if (dcInst)
		DialogueController = dcInst->GetDefaultObject<UDialogueController>();

	auto dpInst = (settings->DefaultDialoguePresenterWidget.IsValid())
		? settings->DefaultDialoguePresenterWidget.Get()				// we have C++ class
		: settings->DefaultDialoguePresenterWidget.LoadSynchronous();	// we have Blueprint class
	if (dcInst)
		DialoguePresenter = CreateWidget<UDialoguePresenterWidget>(owningGame, ipInst);

}
