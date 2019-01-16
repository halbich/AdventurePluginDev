#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBox.h"
#include "ScopedTransaction.h"

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
	TSharedPtr<SHorizontalBox> OutputPinBox;

	virtual TSharedPtr<SBoxPanel> GetMainBox();
	virtual TSharedPtr<SBorder> GetNodeBody();

	virtual FMargin GetInputPinMargin() const { return FMargin(20.0f, 0.0f); }
	virtual FText GetUpperText() const { return FText(); }
	virtual EVisibility GetUpperTextVisibility() const { return EVisibility::Collapsed; }
	virtual FText GetLowerText() const { return FText(); }
	virtual EVisibility GetLowerTextVisibility() const { return EVisibility::Collapsed; }
};
