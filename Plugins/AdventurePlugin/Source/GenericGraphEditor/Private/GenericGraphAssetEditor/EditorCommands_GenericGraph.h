#pragma once

#include "CoreMinimal.h"
#include "Commands.h"
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
	TSharedPtr<FUICommandInfo> AutoArrange;

	virtual void RegisterCommands() override;
};
