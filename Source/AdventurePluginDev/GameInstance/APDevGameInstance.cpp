// Fill out your copyright notice in the Description page of Project Settings.

#include "APDevGameInstance.h"

const FName AP_Log = "AdventurePluginLog";

void UAPDevGameInstance::Init()
{
	Super::Init();

	initCurrentGameContext();

#if WITH_EDITOR

	FString t("DebugSave");
	CurrentGameContext->SaveGame = UAdventurePluginSaveGame::CreateSave(t, 0);

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



	auto dcInst = (settings->DefaultDialogController.IsValid())
		? settings->DefaultDialogController.Get()				// we have C++ class
		: settings->DefaultDialogController.LoadSynchronous();	// we have Blueprint class
	if (dcInst)
		CurrentGameContext->DialogController = dcInst->GetDefaultObject<UDialogController>();

	auto dpInst = (settings->DefaultDialogPresenterWidget.IsValid())
		? settings->DefaultDialogPresenterWidget.Get()				// we have C++ class
		: settings->DefaultDialogPresenterWidget.LoadSynchronous();	// we have Blueprint class
	if (dpInst)
		CurrentGameContext->DialogPresenter = CreateWidget<UDialogPresenterWidget>(this, dpInst);

	auto imInstance = (settings->DefaultItemManager.IsValid())
		? settings->DefaultItemManager.Get()				// we have C++ class
		: settings->DefaultItemManager.LoadSynchronous();	// we have Blueprint class
	if (imInstance)
		CurrentGameContext->ItemManager = imInstance->GetDefaultObject<UItemManager>();

	auto acmInstance = (settings->DefaultAdventureCharacterManager.IsValid())
		? settings->DefaultAdventureCharacterManager.Get()				// we have C++ class
		: settings->DefaultAdventureCharacterManager.LoadSynchronous();	// we have Blueprint class
	if (acmInstance)
		CurrentGameContext->AdventureCharacterManager = acmInstance->GetDefaultObject<UAdventureCharacterManager>();

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
