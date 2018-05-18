// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginInventoryEditorCommands.h"

#define LOCTEXT_NAMESPACE "FAdventurePluginInventoryEditorModule"

void FAdventurePluginInventoryEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "AdventurePluginInventoryEditor", "Bring up AdventurePluginInventoryEditor window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
