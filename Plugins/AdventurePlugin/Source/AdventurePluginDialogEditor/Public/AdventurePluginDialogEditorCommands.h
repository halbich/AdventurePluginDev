// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AdventurePluginDialogEditorStyle.h"

class FAdventurePluginDialogEditorCommands : public TCommands<FAdventurePluginDialogEditorCommands>
{
public:

	FAdventurePluginDialogEditorCommands()
		: TCommands<FAdventurePluginDialogEditorCommands>(TEXT("AdventurePluginDialogEditor"), NSLOCTEXT("Contexts", "AdventurePluginDialogEditor", "AdventurePluginDialogEditor Plugin"), NAME_None, FAdventurePluginDialogEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};