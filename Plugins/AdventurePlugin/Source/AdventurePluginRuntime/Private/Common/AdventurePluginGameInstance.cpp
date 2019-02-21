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
	CurrentGameContext->InventoryController = InstantiateClass(Settings->DefaultInventoryController);
	CurrentGameContext->InventoryPresenter = InstantiateClass(Settings->DefaultInventoryPresenterWidget);
	CurrentGameContext->DialogController = InstantiateClass(Settings->DefaultDialogController);
	CurrentGameContext->DialogPresenter = InstantiateClass(Settings->DefaultDialogPresenterWidget);
	CurrentGameContext->ItemManager = InstantiateClass(Settings->DefaultItemManager);
	CurrentGameContext->AdventureCharacterManager = InstantiateClass(Settings->DefaultAdventureCharacterManager);

}


void UAdventurePluginGameInstance::Shutdown()
{
	Super::Shutdown();

#if WITH_EDITOR
	// opens message log when some warnings occured
	FMessageLog(AP_Log).Open(EMessageSeverity::Type::Warning);
#endif
}
