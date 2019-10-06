#include "Common/AdventurePluginGameInstance.h"

const FName AP_Log = "AdventurePluginLog";

void UAdventurePluginGameInstance::Init()
{
	Super::Init();
	InitCurrentGameContext();

#if WITH_EDITOR
	FString DebugSaveName(TEXT("DebugSave"));
	CurrentGameContext->SaveGame = UAdventurePluginSaveGame::CreateSave(DebugSaveName, 0);
	CurrentGameContext->CombinableObjectManager->ClearMap();
#endif
}

void UAdventurePluginGameInstance::InitCurrentGameContext()
{
	CurrentGameContext = NewObject<UAdventurePluginGameContext>();

	UAdventurePluginConfig* Settings = GetMutableDefault<UAdventurePluginConfig>();
	CurrentGameContext->InventoryController = InstantiateClass(Settings->DefaultInventoryController);
	CurrentGameContext->InventoryPresenter = InstantiateClass(Settings->DefaultInventoryPresenterWidget);
	CurrentGameContext->DialogController = InstantiateClass(Settings->DefaultDialogController);
	CurrentGameContext->DialogPresenter = InstantiateClass(Settings->DefaultDialogPresenterWidget);
	CurrentGameContext->CombinableObjectManager = InstantiateClass(Settings->DefaultCombinableObjectManager);
	//The save game is required for context to be valid, so ensure that a save is used. 
	FString InitialSave(TEXT("InitialSave"));
	CurrentGameContext->SaveGame = UAdventurePluginSaveGame::CreateSave(InitialSave, 0);
	if (!IsValid(CurrentGameContext->SaveGame))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "InitGameContextSaveInvalid", "Could not initialize game context"));
	}
}


void UAdventurePluginGameInstance::Shutdown()
{
	Super::Shutdown();

#if WITH_EDITOR
	// opens message log when some warnings occured
	FMessageLog(AP_Log).Open(EMessageSeverity::Type::Warning);
#endif
}

UAdventurePluginGameContext* UAdventurePluginGameInstance::GetDefaultGameContext_Implementation()
{
	return CurrentGameContext;
}
