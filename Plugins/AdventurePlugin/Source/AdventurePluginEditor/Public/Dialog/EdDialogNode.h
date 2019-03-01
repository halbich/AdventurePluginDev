#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "Dialog/SEdDialogNode.h"
#include "EdDialogNode.generated.h"

/**
* Class representing dialog node behavior in editor (its pins, copying/deleting etc.)
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode : public UEdNode_GenericGraphNode
{
	GENERATED_BODY()

public:

	UEdDialogNode() { }
	virtual ~UEdDialogNode() { }

	/**
	* Creates a visual widget to represent this node in a graph editor or graph panel.
	* @return Widget representing this node
	*/
	virtual TSharedPtr<class SGraphNode> CreateVisualWidget() override
	{
		return SNew(SEdDialogNode, this);
	}
};