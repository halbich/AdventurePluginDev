#include "Dialog/SEdDialogNode_Options.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "GenericGraph/GenericGraphNode.h"
#include "Dialog/Graph/DialogGraphNode_Options.h"
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
	UEdNode_GenericGraphNode* StateNode = CastChecked<UEdNode_GenericGraphNode>(GraphNode);
	UDialogGraphNode_Options* OptionsNode = CastChecked<UDialogGraphNode_Options>(DialogGraphNode);

	int32 ChoiceCount = OptionsNode->ChoiceCount;
	for (int32 i = StateNode->Pins.Num() - 1; i <= ChoiceCount; ++i)
	{
		StateNode->CreatePin(EGPD_Output, "MultipleNodes", FName(), FName(*FString::FromInt(i)));
	}
	for (int32 i = StateNode->Pins.Num() - 2; i > ChoiceCount; --i)
	{
		StateNode->RemovePinAt(i, EGPD_Output);
	}

	// INPUT PIN
	TSharedPtr<SGraphPin> NewPin = SNew(SGenericGraphPin, StateNode->Pins[0]);
	AddPin(NewPin.ToSharedRef());

	// FALLBACK PIN
	NewPin = SNew(SGenericGraphPin, StateNode->Pins[1]);
	const TSharedRef<SGraphPin>& PinToAdd = NewPin.ToSharedRef();
	PinToAdd->SetOwner(SharedThis(this));
	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();
	const bool bAdvancedParameter = PinObj && PinObj->bAdvancedView;
	if (bAdvancedParameter)
	{
		PinToAdd->SetVisibility(TAttribute<EVisibility>(PinToAdd, &SGraphPin::IsPinVisibleAsAdvanced));
	}
	AddToVerticalBox(LeftNodeBox, PinToAdd);
	OutputPins.Add(PinToAdd);

	// REST OF PINS
	for (int32 PinIdx = 2; PinIdx < StateNode->Pins.Num(); PinIdx++)
	{
		UEdGraphPin* MyPin = StateNode->Pins[PinIdx];
		if (!MyPin->bHidden)
		{
			NewPin = SNew(SGenericGraphPin, MyPin);
			AddPin(NewPin.ToSharedRef());
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SEdDialogNode_Options::IncrementOptionsCount()
{
	UDialogGraphNode_Options* OptionsNode = CastChecked<UDialogGraphNode_Options>(DialogGraphNode);
	OptionsNode->ChoiceCount++;
	UpdateGraphNode();
	return FReply::Handled();
}

FReply SEdDialogNode_Options::DecrementOptionsCount()
{
	UDialogGraphNode_Options* OptionsNode = CastChecked<UDialogGraphNode_Options>(DialogGraphNode);
	if (OptionsNode->ChoiceCount > 1)
	{
		OptionsNode->ChoiceCount--;
		UpdateGraphNode();
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE