#pragma once

#include "CoreMinimal.h"
#include "Dialog/SEdDialogNode.h"

/**
* Special Slate widget for representing graph node of type UDialogGraphNode_Options in the graph editor.
* It adds +/- buttons to the node body for adding and removing output pins.
*/
class ADVENTUREPLUGINEDITOR_API SEdDialogNode_Options : public SEdDialogNode
{
public:

	/**
	* Creates the widgets for pins on the node, according to the ChoiceCount
	* on the underlying UDialogGraphNode_Options node.
	*/
	virtual void CreatePinWidgets() override;

protected:

	/*
	* Creates the default body of the node, then adds two buttons +/- for adding
	* and removing output pins.
	* @return Body of the node
	*/
	virtual TSharedPtr<SBorder> GetNodeBody() override;

	/**
	* Method is called when the '+' button is pressed. It increments the ChoiceCount
	* on the underlying UDialogGraphNode_Options node and redraws the widget.
	*/
	virtual FReply IncrementOptionsCount();

	/**
	* Method is called when the '-' button is pressed. It decrements the ChoiceCount
	* on the underlying UDialogGraphNode_Options node and redraws the widget.
	*/
	virtual FReply DecrementOptionsCount();
};