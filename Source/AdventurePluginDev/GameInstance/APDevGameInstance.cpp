// Fill out your copyright notice in the Description page of Project Settings.

#include "APDevGameInstance.h"
#include "MessageLogModule.h"
#include "IMessageLogListing.h"

const FName AP_Log = "AdventurePluginLog";

void UAPDevGameInstance::Init()
{
	Super::Init();

	initCurrentGameContext();

#if WITH_EDITOR
	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
	{
		// Clear errors from log
		MessageLogModule.GetLogListing(AP_Log)->ClearMessages();
	}
#endif
}

void UAPDevGameInstance::initCurrentGameContext()
{
	CurrentGameContext = NewObject<UAdventurePluginGameContext>();

	auto settings = GetMutableDefault<UAdventurePluginConfig>();

	auto icInst = (settings->DefaultInventoryController.IsValid())
		? settings->DefaultInventoryController.Get()				// we have C++ class
		: settings->DefaultInventoryController.LoadSynchronous();	// we have Blueprint class
	if (icInst)
		CurrentGameContext->InventoryController = icInst->GetDefaultObject<UInventoryController>();

	auto ipInst = (settings->DefaultInventoryPresenterWidget.IsValid())
		? settings->DefaultInventoryPresenterWidget.Get()				// we have C++ class
		: settings->DefaultInventoryPresenterWidget.LoadSynchronous();	// we have Blueprint class
	if (ipInst)
		CurrentGameContext->InventoryPresenter = CreateWidget<UInventoryPresenterWidget>(this, ipInst);



	auto dcInst = (settings->DefaultDialogueController.IsValid())
		? settings->DefaultDialogueController.Get()				// we have C++ class
		: settings->DefaultDialogueController.LoadSynchronous();	// we have Blueprint class
	if (dcInst)
		CurrentGameContext->DialogueController = dcInst->GetDefaultObject<UDialogueController>();

	auto dpInst = (settings->DefaultDialoguePresenterWidget.IsValid())
		? settings->DefaultDialoguePresenterWidget.Get()				// we have C++ class
		: settings->DefaultDialoguePresenterWidget.LoadSynchronous();	// we have Blueprint class
	if (dpInst)
		CurrentGameContext->DialoguePresenter = CreateWidget<UDialoguePresenterWidget>(this, dpInst);

	auto imInstance = (settings->DefaultItemManager.IsValid())
		? settings->DefaultItemManager.Get()				// we have C++ class
		: settings->DefaultItemManager.LoadSynchronous();	// we have Blueprint class
	if (imInstance)
		CurrentGameContext->ItemManager = imInstance->GetDefaultObject<UItemManager>();

}


void UAPDevGameInstance::Shutdown()
{
	Super::Shutdown();

#if WITH_EDITOR
	// opens message log when some warnings occured
	FMessageLog(AP_Log).Open(EMessageSeverity::Type::Warning);
#endif
}




#pragma optimize("", off)
void UAPDevGameInstance::TestContext()
{

	if (CurrentGameContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("AAA"));
	}

}

#pragma optimize("", on)
