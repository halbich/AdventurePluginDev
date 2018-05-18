// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AdventurePluginInventoryEditorStyle.h"

class FAdventurePluginInventoryEditorCommands : public TCommands<FAdventurePluginInventoryEditorCommands>
{
public:

	FAdventurePluginInventoryEditorCommands()
		: TCommands<FAdventurePluginInventoryEditorCommands>(TEXT("AdventurePluginInventoryEditor"), NSLOCTEXT("Contexts", "AdventurePluginInventoryEditor", "AdventurePluginInventoryEditor Plugin"), NAME_None, FAdventurePluginInventoryEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};