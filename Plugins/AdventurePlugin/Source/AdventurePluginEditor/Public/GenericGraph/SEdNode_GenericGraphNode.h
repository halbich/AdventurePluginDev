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

class ADVENTUREPLUGINEDITOR_API SEdNode_GenericGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SEdNode_GenericGraphNode) {}
	SLATE_END_ARGS()

	virtual void Construct(const FArguments& InArgs, UEdNode_GenericGraphNode* InNode);

	virtual void UpdateGraphNode() override;
	virtual void CreatePinWidgets() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
	virtual bool IsNameReadOnly() const override;

	void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo);

	virtual FSlateColor GetBorderBackgroundColor() const;
	virtual FSlateColor GetBackgroundColor() const;

	virtual EVisibility GetDragOverMarkerVisibility() const;

	virtual const FSlateBrush* GetNameIcon() const;

protected:
	TSharedPtr<SBorder> NodeBody;
	TSharedPtr<SHorizontalBox> TopNodeBox;
	TSharedPtr<SHorizontalBox> BottomNodeBox;

	void AddToHorizontalBox(TSharedPtr<SHorizontalBox> Box, const TSharedRef<SGraphPin>& PinToAdd);
	void AddToVerticalBox(TSharedPtr<SVerticalBox> Box, const TSharedRef<SGraphPin>& PinToAdd);

	virtual TSharedPtr<SBoxPanel> GetMainBox();
	virtual TSharedPtr<SBorder> GetNodeBody();

	virtual bool IsGraphHorizontal() const { return false; }
	virtual FText GetUpperText() const { return FText(); }
	virtual EVisibility GetUpperTextVisibility() const { return EVisibility::Collapsed; }
	virtual FText GetLowerText() const { return FText(); }
	virtual EVisibility GetLowerTextVisibility() const { return EVisibility::Collapsed; }
};

class SGenericGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SGenericGraphPin) {}
	SLATE_END_ARGS()

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
	virtual FSlateColor GetPinColor() const override
	{
		return GenericGraphColors::Pin::Default;
	}

	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override
	{
		return SNew(STextBlock);
	}

	const FSlateBrush* GetPinBorder() const
	{
		return FEditorStyle::GetBrush(TEXT("Graph.StateNode.Body"));
	}
};
