#include "Dialogue/SEdDialogNode_TrueFalse.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "GenericGraph/GenericGraphNode.h"

#define LOCTEXT_NAMESPACE "SEdDialogNode_TrueFalse"

void SEdDialogNode_TrueFalse::CreatePinWidgets()
{
	SEdDialogNode::CreatePinWidgets();

	UEdNode_GenericGraphNode* StateNode = CastChecked<UEdNode_GenericGraphNode>(GraphNode);
	check(StateNode->Pins.Num() == 3);

	UEdGraphPin* PinTrue = StateNode->Pins[1];
	check(PinTrue->Direction == EEdGraphPinDirection::EGPD_Output);
	PinTrue->PinFriendlyName = LOCTEXT("PinTrue", "True");

	UEdGraphPin* PinFalse = StateNode->Pins[2];
	check(PinFalse->Direction == EEdGraphPinDirection::EGPD_Output);
	PinFalse->PinFriendlyName = LOCTEXT("PinFalse", "False");
}

#undef LOCTEXT_NAMESPACE