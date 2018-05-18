// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginStoryEngineEditorCommands.h"

#define LOCTEXT_NAMESPACE "FAdventurePluginStoryEngineEditorModule"

void FAdventurePluginStoryEngineEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "AdventurePluginStoryEngineEditor", "Bring up AdventurePluginStoryEngineEditor window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
