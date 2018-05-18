// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TestEditorStandaloneCommands.h"

#define LOCTEXT_NAMESPACE "FTestEditorStandaloneModule"

void FTestEditorStandaloneCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "TestEditorStandalone", "Bring up TestEditorStandalone window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
