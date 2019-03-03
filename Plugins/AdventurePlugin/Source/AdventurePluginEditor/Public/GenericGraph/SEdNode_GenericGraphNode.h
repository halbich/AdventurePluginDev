/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBox.h"
#include "ScopedTransaction.h"
#include "SGraphPin.h"
#include "GenericGraph/Colors_GenericGraph.h"

class UEdNode_GenericGraphNode;

/**
* Default Slate widget representing UGenericGraphNode in the graph editor
*/
class ADVENTUREPLUGINEDITOR_API SEdNode_GenericGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SEdNode_GenericGraphNode) {}
	SLATE_END_ARGS()

	/**
	* Constructs this widget
	* @param	InNode	The editor node to create a widget for
	*/
	virtual void Construct(const FArguments& InArgs, UEdNode_GenericGraphNode* InNode);

	/**
	* Updates this GraphNode to match the data that it is observing.
	*/
	virtual void UpdateGraphNode() override;

	/**
	* Creates the widgets for pins on the node.
	*/
	virtual void CreatePinWidgets() override;

	/**
	* Adds a new pin to this graph node. The pin must be newly created.
	* @param PinToAdd   A new pin to add to this GraphNode.
	*/
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;

	/**
	* Helper function to check if node can be renamed.
	* @return True if the node's name is read only
	*/
	virtual bool IsNameReadOnly() const override;

	/**
	* Called when text is committed on the node
	*/
	void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo);

	/**
	* Returns border color for this node, extracted from the associated
	* generic editor node by UEdNode_GenericGraphNode#GetBackgroundColor.
	*/
	virtual FSlateColor GetBorderBackgroundColor() const;

	/**
	* Returns default background color for nodes.
	*/
	virtual FSlateColor GetBackgroundColor() const;

protected:

	/** Body of the node for showing its content, without all input/output pin boxes */
	TSharedPtr<SBorder> NodeBody;

	/** The upper area where input pins reside */
	TSharedPtr<SHorizontalBox> TopNodeBox;

	/** The lower area where output pins reside */
	TSharedPtr<SHorizontalBox> BottomNodeBox;

	/**
	* Adds the new (input or output) pin to the horizontal pin box. 
	* Meant for TopNodeBox or BottomNodeBox.
	* @param Box SHorizontalBox widget to add the pin into
	* @param PinToAdd The pin to add
	*/
	void AddToHorizontalBox(TSharedPtr<SHorizontalBox> Box, const TSharedRef<SGraphPin>& PinToAdd);

	/**
	* Adds the new (input or output) pin to the vertical pin box.
	* Meant for LeftNodeBox or RightNodeBox.
	* @param Box SVerticalBox widget to add the pin into
	* @param PinToAdd The pin to add
	*/
	void AddToVerticalBox(TSharedPtr<SVerticalBox> Box, const TSharedRef<SGraphPin>& PinToAdd);

	/**
	* Creates the main box of the node. It includes everything except outer border of the node.
	* This can be overriden if the node should look quite different, including all the pins.
	* @return Main box of the node
	*/
	virtual TSharedPtr<SBoxPanel> GetMainBox();

	/**
	* Creates the body of the node. It includes only the content area,
	* without any input/output pin boxes. This can be overriden if
	* the node should look different, but the pin areas should remain the same.
	* @return Body of the node
	*/
	virtual TSharedPtr<SBorder> GetNodeBody();

	/**
	* Returns whether the graph is horizontal or not. If it is, LeftNodeBox and RightNodeBox
	* are used for storing pins, otherwise TopNodeBox and BottomNodeBox are used.
	* @return True, if the graph is horizontal
	*/
	virtual bool IsGraphHorizontal() const { return false; }

	/**
	* Returns the text which should be displayed in the SEdNode_GenericGraphNode#NodeBody, above the node title.
	* @return The upper text
	*/
	virtual FText GetUpperText() const { return FText(); }

	/**
	* @return The desired visibility of the upper text in the SEdNode_GenericGraphNode#NodeBody area
	*/
	virtual EVisibility GetUpperTextVisibility() const { return EVisibility::Collapsed; }

	/**
	* Returns the text which should be displayed in the SEdNode_GenericGraphNode#NodeBody, under the node title.
	* @return The lower text
	*/
	virtual FText GetLowerText() const { return FText(); }

	/**
	* @return The desired visibility of the lower text in the SEdNode_GenericGraphNode#NodeBody area
	*/
	virtual EVisibility GetLowerTextVisibility() const { return EVisibility::Collapsed; }
};

/**
 * Default Slate widget representing a pin on a generic graph node in the graph editor
 */
class SGenericGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SGenericGraphPin) {}
	SLATE_END_ARGS()

	/**
	* Constructs this widget
	* @param	InPin	The pin to create a widget for
	*/
	void Construct(const FArguments& InArgs, UEdGraphPin* InPin)
	{
		this->SetCursor(EMouseCursor::Default);

		bShowLabel = true;

		GraphPinObj = InPin;
		check(GraphPinObj != nullptr);

		const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
		check(Schema);

		SBorder::Construct(SBorder::FArguments()
			.BorderImage(this, &SGenericGraphPin::GetPinBorder)
			.BorderBackgroundColor(this, &SGenericGraphPin::GetPinColor)
			.OnMouseButtonDown(this, &SGenericGraphPin::OnPinMouseDown)
			.Cursor(this, &SGenericGraphPin::GetPinCursor)
			.HAlign(EHorizontalAlignment::HAlign_Center)
			.VAlign(EVerticalAlignment::VAlign_Center)
			.Padding(FMargin(10, 0))
			.Content()
			[
				GetLabelWidget(FName())
			]
		);
	}

protected:

	/**
	* @return The color that we should use to draw this pin
	*/
	virtual FSlateColor GetPinColor() const override
	{
		return GenericGraphColors::Pin::Default;
	}

	/**
	* @return The widget we should put into the 'default value' space, shown when nothing connected.
	*/
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override
	{
		return SNew(STextBlock);
	}

	const FSlateBrush* GetPinBorder() const
	{
		return FEditorStyle::GetBrush(TEXT("Graph.StateNode.Body"));
	}
};
