// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AdventurePluginStoryEngineEditorStyle.h"

class FAdventurePluginStoryEngineEditorCommands : public TCommands<FAdventurePluginStoryEngineEditorCommands>
{
public:

	FAdventurePluginStoryEngineEditorCommands()
		: TCommands<FAdventurePluginStoryEngineEditorCommands>(TEXT("AdventurePluginStoryEngineEditor"), NSLOCTEXT("Contexts", "AdventurePluginStoryEngineEditor", "AdventurePluginStoryEngineEditor Plugin"), NAME_None, FAdventurePluginStoryEngineEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};