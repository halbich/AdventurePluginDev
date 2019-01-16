#include "Dialogue/SEdDialogNode_LessEqualMore.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "GenericGraph/GenericGraphNode.h"

#define LOCTEXT_NAMESPACE "SEdDialogNode_LessEqualMore"

void SEdDialogNode_LessEqualMore::CreatePinWidgets()
{
	SEdDialogNode::CreatePinWidgets();

	UEdNode_GenericGraphNode* StateNode = CastChecked<UEdNode_GenericGraphNode>(GraphNode);
	check(StateNode->Pins.Num() == 4);

	UEdGraphPin* PinLess = StateNode->Pins[1];
	check(PinLess->Direction == EEdGraphPinDirection::EGPD_Output);
	PinLess->PinFriendlyName = LOCTEXT("PinLess", "<");

	UEdGraphPin* PinEqual = StateNode->Pins[2];
	check(PinEqual->Direction == EEdGraphPinDirection::EGPD_Output);
	PinEqual->PinFriendlyName = LOCTEXT("PinEqual", "=");

	UEdGraphPin* PinMore = StateNode->Pins[3];
	check(PinMore->Direction == EEdGraphPinDirection::EGPD_Output);
	PinMore->PinFriendlyName = LOCTEXT("PinMore", ">");
}

#undef LOCTEXT_NAMESPACE