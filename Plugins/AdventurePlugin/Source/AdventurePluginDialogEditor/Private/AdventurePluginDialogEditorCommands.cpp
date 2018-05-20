// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginDialogEditorCommands.h"

#define LOCTEXT_NAMESPACE "FAdventurePluginDialogEditorModule"

void FAdventurePluginDialogEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Dialog Editor", "Bring up AdventurePluginDialogEditor window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
