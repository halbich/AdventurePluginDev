#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "Quest/SEdQuestNode.h"
#include "EdQuestNode.generated.h"

/**
* Class representing quest node behavior in editor (its pins, copying/deleting etc.)
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdQuestNode : public UEdNode_GenericGraphNode
{
	GENERATED_BODY()

public:

	UEdQuestNode() { }
	virtual ~UEdQuestNode() { }

	/**
	* Creates a visual widget to represent this node in a graph editor or graph panel.
	* @return Widget representing this node
	*/
	virtual TSharedPtr<class SGraphNode> CreateVisualWidget() override
	{
		return SNew(SEdQuestNode, this);
	}
};