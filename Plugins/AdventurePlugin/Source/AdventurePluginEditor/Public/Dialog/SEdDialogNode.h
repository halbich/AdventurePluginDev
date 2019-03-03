#pragma once

#include "CoreMinimal.h"
#include "Dialog/Graph/DialogGraphNode.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "GenericGraph/SEdNode_GenericGraphNode.h"

/**
* Slate widget for representing UDialogGraphNode in the graph editor
*/
class ADVENTUREPLUGINEDITOR_API SEdDialogNode : public SEdNode_GenericGraphNode
{
public:

	virtual void Construct(const FArguments& InArgs, UEdNode_GenericGraphNode* InNode) override;

protected:

	/** The runtime Dialog graph node visualized by this widget */
	UDialogGraphNode* DialogGraphNode;

	/**
	* Returns the text which should be displayed in the SEdNode_GenericGraphNode#NodeBody, above the node title.
	* In this case, it is the UDialogGraphNode#Id, if set.
	* @return The upper text
	*/
	virtual FText GetUpperText() const override;

	/**
	* @return Visible, when there is text to show, Collapsed otherwise
	*/
	virtual EVisibility GetUpperTextVisibility() const override;

	/**
	* Returns the text which should be displayed in the SEdNode_GenericGraphNode#NodeBody, under the node title.
	* In this case, it is the UDialogGraphNode#Note, if set.
	* @return The lower text
	*/
	virtual FText GetLowerText() const override;

	/**
	* @return Visible, when there is text to show, Collapsed otherwise
	*/
	virtual EVisibility GetLowerTextVisibility() const override;
};