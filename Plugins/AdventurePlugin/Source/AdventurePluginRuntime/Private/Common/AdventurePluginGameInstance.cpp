// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginGameInstance.h"

const FName AP_Log = "AdventurePluginLog";

void UAdventurePluginGameInstance::Init()
{
	Super::Init();

	InitCurrentGameContext();

#if WITH_EDITOR

	FString DebugSaveName("DebugSave");
	CurrentGameContext->SaveGame = UAdventurePluginSaveGame::CreateSave(DebugSaveName, 0);
	CurrentGameContext->ItemManager->ClearMap();
	CurrentGameContext->AdventureCharacterManager->ClearMap();

#endif
}

void UAdventurePluginGameInstance::InitCurrentGameContext()
{
	//TODO: Is this correct? Using CDO's as managers?
	CurrentGameContext = NewObject<UAdventurePluginGameContext>();

	UAdventurePluginConfig* Settings = GetMutableDefault<UAdventurePluginConfig>();
	//TODO: Copy pasting. This should be in a templated method, or somehow else refactored.
	UClass* InventoryControllerClass = (Settings->DefaultInventoryController.IsValid())
		? Settings->DefaultInventoryController.Get()				// we have C++ class
		: Settings->DefaultInventoryController.LoadSynchronous();	// we have Blueprint class
	if (InventoryControllerClass)
		CurrentGameContext->InventoryController = InventoryControllerClass->GetDefaultObject<UInventoryController>();

	UClass* InventoryPresenterClass = (Settings->DefaultInventoryPresenterWidget.IsValid())
		? Settings->DefaultInventoryPresenterWidget.Get()				// we have C++ class
		: Settings->DefaultInventoryPresenterWidget.LoadSynchronous();	// we have Blueprint class
	//TODO: What if it's not a widget?
	if (InventoryPresenterClass)
		CurrentGameContext->InventoryPresenter = CreateWidget<UInventoryPresenterWidget>(this, InventoryPresenterClass);



	UClass* DialogControllerClass = (Settings->DefaultDialogController.IsValid())
		? Settings->DefaultDialogController.Get()				// we have C++ class
		: Settings->DefaultDialogController.LoadSynchronous();	// we have Blueprint class
	if (DialogControllerClass)
		CurrentGameContext->DialogController = DialogControllerClass->GetDefaultObject<UDialogController>();

	UClass* DialogPresenterClass = (Settings->DefaultDialogPresenterWidget.IsValid())
		? Settings->DefaultDialogPresenterWidget.Get()				// we have C++ class
		: Settings->DefaultDialogPresenterWidget.LoadSynchronous();	// we have Blueprint class
	//TODO: What if it's not a widget?
	if (DialogPresenterClass)
		CurrentGameContext->DialogPresenter = CreateWidget<UDialogPresenterWidget>(this, DialogPresenterClass);

	UClass* InventoryManagerClass = (Settings->DefaultItemManager.IsValid())
		? Settings->DefaultItemManager.Get()				// we have C++ class
		: Settings->DefaultItemManager.LoadSynchronous();	// we have Blueprint class
	if (InventoryManagerClass)
		CurrentGameContext->ItemManager = InventoryManagerClass->GetDefaultObject<UItemManager>();

	UClass* AdventureCharacterManagerClass = (Settings->DefaultAdventureCharacterManager.IsValid())
		? Settings->DefaultAdventureCharacterManager.Get()				// we have C++ class
		: Settings->DefaultAdventureCharacterManager.LoadSynchronous();	// we have Blueprint class
	if (AdventureCharacterManagerClass)
		CurrentGameContext->AdventureCharacterManager = AdventureCharacterManagerClass->GetDefaultObject<UAdventureCharacterManager>();

}


void UAdventurePluginGameInstance::Shutdown()
{
	Super::Shutdown();

#if WITH_EDITOR
	// opens message log when some warnings occured
	FMessageLog(AP_Log).Open(EMessageSeverity::Type::Warning);
#endif
}
