/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#include "GenericGraph/EditorCommands_GenericGraph.h"

#define LOCTEXT_NAMESPACE "EditorCommands_GenericGraph"

void FEditorCommands_GenericGraph::RegisterCommands()
{
	UI_COMMAND(GraphSettings, "Graph Settings", "Graph Settings", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
