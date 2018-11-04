// Fill out your copyright notice in the Description page of Project Settings.

#include "APDevGameInstance.h"
#include "MessageLogModule.h"
#include "IMessageLogListing.h"

const FName AP_Log = "AdventurePluginLog";

void UAPDevGameInstance::Init()
{
	Super::Init();

	CurrentGameContext = NewObject<UAdventurePluginGameContext>();
	CurrentGameContext->InitFromConfig(this);

#if WITH_EDITOR
	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
	{
		// Clear errors from log
		MessageLogModule.GetLogListing(AP_Log)->ClearMessages();
	}
#endif
}

void UAPDevGameInstance::Shutdown()
{
	Super::Shutdown();

#if WITH_EDITOR
	// opens message log when some warnings occured
	FMessageLog(AP_Log).Open(EMessageSeverity::Type::Warning);
#endif
}


