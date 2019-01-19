#include "Dialogue/SEdDialogNode_Options.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "GenericGraph/GenericGraphNode.h"
#include "Dialogue/Graph/DialogGraphNode_Options.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"

#define LOCTEXT_NAMESPACE "SEdDialogNode_Options"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedPtr<SBorder> SEdDialogNode_Options::GetNodeBody()
{
	return SAssignNew(NodeBody, SBorder)
	.Padding(0)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.FillHeight(1.0)
			[
				SEdDialogNode::GetNodeBody().ToSharedRef()
			]
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.FillHeight(0.5)
			[
				SNew(SButton)
				.ContentPadding(FMargin(4.0f, 0.0f))
				.HAlign(EHorizontalAlignment::HAlign_Center)
				.VAlign(EVerticalAlignment::VAlign_Center)
				.Text(LOCTEXT("PlusButton", "+"))
				.OnClicked_Raw(this, &SEdDialogNode_Options::IncrementOptionsCount)
			]
			+ SVerticalBox::Slot()
			.FillHeight(0.5)
			[
				SNew(SButton)
				.ContentPadding(FMargin(4.0f, 0.0f))
				.HAlign(EHorizontalAlignment::HAlign_Center)
				.VAlign(EVerticalAlignment::VAlign_Center)
				.Text(LOCTEXT("MinusButton", "-"))
				.OnClicked(this, &SEdDialogNode_Options::DecrementOptionsCount)
			]
		]
	];
}

void SEdDialogNode_Options::CreatePinWidgets()
{
	SEdDialogNode::CreatePinWidgets();

	UEdNode_GenericGraphNode* StateNode = CastChecked<UEdNode_GenericGraphNode>(GraphNode);

	for (int i = 1; i < StateNode->Pins.Num(); ++i)
	{
		UEdGraphPin* Pin = StateNode->Pins[i];
		check(Pin->Direction == EEdGraphPinDirection::EGPD_Output);
		Pin->PinFriendlyName = FText::AsNumber(i);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SEdDialogNode_Options::IncrementOptionsCount()
{
	auto OptionsNode = CastChecked<UDialogGraphNode_Options>(DialogGraphNode);
	OptionsNode->ChoiceCount++;
	UpdateGraphNode();
	return FReply::Handled();
}

FReply SEdDialogNode_Options::DecrementOptionsCount()
{
	auto OptionsNode = CastChecked<UDialogGraphNode_Options>(DialogGraphNode);
	if (OptionsNode->ChoiceCount > 1)
	{
		OptionsNode->ChoiceCount--;
		UpdateGraphNode();
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE