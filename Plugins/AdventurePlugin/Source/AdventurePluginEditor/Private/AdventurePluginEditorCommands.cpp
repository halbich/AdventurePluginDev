// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginEditorCommands.h"

#define LOCTEXT_NAMESPACE "FAdventurePluginEditorModule"

void FAdventurePluginEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "AdventurePluginEditor", "Bring up AdventurePluginEditor window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
