/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EditorStyleSet.h"

class FEditorCommands_GenericGraph : public TCommands<FEditorCommands_GenericGraph>
{
public:
	/** Constructor */
	FEditorCommands_GenericGraph()
		: TCommands<FEditorCommands_GenericGraph>("GenericGraphEditor", NSLOCTEXT("Contexts", "GenericGraphEditor", "Generic Graph Editor"), NAME_None, FEditorStyle::GetStyleSetName())
	{
	}

	virtual ~FEditorCommands_GenericGraph()
	{
	}
	
	TSharedPtr<FUICommandInfo> GraphSettings;

	virtual void RegisterCommands() override;
};
