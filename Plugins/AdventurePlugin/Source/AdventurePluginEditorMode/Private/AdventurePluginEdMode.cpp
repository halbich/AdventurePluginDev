// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginEdMode.h"
#include "AdventurePluginEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FAdventurePluginEdMode::EM_AdventurePluginEdModeId = TEXT("EM_AdventurePluginEdMode");

FAdventurePluginEdMode::FAdventurePluginEdMode()
{

}

FAdventurePluginEdMode::~FAdventurePluginEdMode()
{

}

void FAdventurePluginEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FAdventurePluginEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FAdventurePluginEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FAdventurePluginEdMode::UsesToolkits() const
{
	return true;
}




