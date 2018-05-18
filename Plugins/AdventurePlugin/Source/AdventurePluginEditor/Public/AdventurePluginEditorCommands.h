// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AdventurePluginEditorStyle.h"

class FAdventurePluginEditorCommands : public TCommands<FAdventurePluginEditorCommands>
{
public:

	FAdventurePluginEditorCommands()
		: TCommands<FAdventurePluginEditorCommands>(TEXT("AdventurePluginEditor"), NSLOCTEXT("Contexts", "AdventurePluginEditor", "AdventurePluginEditor Plugin"), NAME_None, FAdventurePluginEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};