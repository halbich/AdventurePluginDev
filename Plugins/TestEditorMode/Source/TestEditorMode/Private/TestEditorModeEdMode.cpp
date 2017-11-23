// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TestEditorModeEdMode.h"
#include "TestEditorModeEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FTestEditorModeEdMode::EM_TestEditorModeEdModeId = TEXT("EM_TestEditorModeEdMode");

FTestEditorModeEdMode::FTestEditorModeEdMode()
{

}

FTestEditorModeEdMode::~FTestEditorModeEdMode()
{

}

void FTestEditorModeEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FTestEditorModeEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FTestEditorModeEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FTestEditorModeEdMode::UsesToolkits() const
{
	return true;
}




