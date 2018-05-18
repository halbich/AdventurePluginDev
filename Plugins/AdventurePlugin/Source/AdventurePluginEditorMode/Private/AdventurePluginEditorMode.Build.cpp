// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginEditorMode.h"
#include "AdventurePluginEdMode.h"

#define LOCTEXT_NAMESPACE "FAdventurePluginEditorModeModule"

void FAdventurePluginEditorModeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FAdventurePluginEdMode>(FAdventurePluginEdMode::EM_AdventurePluginEdModeId, LOCTEXT("AdventurePluginEdModeName", "AdventurePluginEdMode"), FSlateIcon(), true);
}

void FAdventurePluginEditorModeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FAdventurePluginEdMode::EM_AdventurePluginEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAdventurePluginEditorModeModule, AdventurePluginEditorMode)