#pragma once

#include "CoreMinimal.h"
#include "Quest/Graph/QuestGraphNode.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "GenericGraph/SEdNode_GenericGraphNode.h"

/**
* Slate widget for representing UQuestGraphNode in the graph editor
*/
class ADVENTUREPLUGINEDITOR_API SEdQuestNode : public SEdNode_GenericGraphNode
{
public:

	virtual void Construct(const FArguments& InArgs, UEdNode_GenericGraphNode* InNode) override;

protected:

	/** The runtime Quest graph node visualized by this widget */
	UQuestGraphNode* QuestGraphNode;

	virtual bool IsGraphHorizontal() const override { return true; }

	/**
	* Returns the text which should be displayed in the SEdNode_GenericGraphNode#NodeBody, above the node title.
	* In this case, it is the UQuestGraphNode#Location, if set.
	* @return The upper text
	*/
	virtual FText GetUpperText() const override;

	/**
	* @return Visible, when there is text to show, Collapsed otherwise
	*/
	virtual EVisibility GetUpperTextVisibility() const override;
};