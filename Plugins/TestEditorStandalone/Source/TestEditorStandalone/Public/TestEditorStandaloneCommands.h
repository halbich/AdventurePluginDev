// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TestEditorStandaloneStyle.h"

class FTestEditorStandaloneCommands : public TCommands<FTestEditorStandaloneCommands>
{
public:

	FTestEditorStandaloneCommands()
		: TCommands<FTestEditorStandaloneCommands>(TEXT("TestEditorStandalone"), NSLOCTEXT("Contexts", "TestEditorStandalone", "TestEditorStandalone Plugin"), NAME_None, FTestEditorStandaloneStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};