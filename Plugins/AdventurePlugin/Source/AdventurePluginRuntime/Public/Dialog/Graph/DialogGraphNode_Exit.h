#pragma once

#include "CoreMinimal.h"
#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_Exit.generated.h"

/**
* This node marks the end of the graph, does nothing.
* It exists to clearly mark that we expect the dialog to end here.
* In the future we might want to add some warning if the execution ends anywhere else to avoid ending dialogs by mistake.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Exit : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Exit()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("AdventurePlugin", "UDialogGraphNode_Exit_ContextName", "Exit");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "OtherCategory", "Other");
#endif
	}

	virtual ~UDialogGraphNode_Exit()
	{
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::FromString("EXIT");
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::White;
	}

#endif
};
