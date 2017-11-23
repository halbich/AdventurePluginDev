// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TestEditorMode.h"
#include "TestEditorModeEdMode.h"

#define LOCTEXT_NAMESPACE "FTestEditorModeModule"

void FTestEditorModeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FTestEditorModeEdMode>(FTestEditorModeEdMode::EM_TestEditorModeEdModeId, LOCTEXT("TestEditorModeEdModeName", "TestEditorModeEdMode"), FSlateIcon(), true);
}

void FTestEditorModeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FTestEditorModeEdMode::EM_TestEditorModeEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTestEditorModeModule, TestEditorMode)