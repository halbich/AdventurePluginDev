#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialog/EdDialogNode.h"
#include "Dialog/Graph/DialogGraphNode_IfInteger.h"
#include "EdDialogNode_LessEqualMore.generated.h"

const FName PinNameLess("<");
const FName PinNameEqual("=");
const FName PinNameMore(">");

/**
* Class representing behavior of a dialog node with one input pin and three output pins
* labeled "<", "=" and ">".
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_LessEqualMore : public UEdDialogNode
{
	GENERATED_BODY()

public:

	UEdDialogNode_LessEqualMore() { }
	virtual ~UEdDialogNode_LessEqualMore() { }

	/**
	* Allocates default pins for a LessEqualMore node, one input and three outputs.
	*/
	virtual void AllocateDefaultPins() override
	{
		CreatePin(EGPD_Input, "MultipleNodes", FName(), FName());
		CreatePin(EGPD_Output, "MultipleNodes", FName(), PinNameLess);
		CreatePin(EGPD_Output, "MultipleNodes", FName(), PinNameEqual);
		CreatePin(EGPD_Output, "MultipleNodes", FName(), PinNameMore);
	}

	/**
	* This method is called when the graph is rebuilding, for every output pin and
	* the node connected to it. It sets the child node to the parent's UDialogGraphNode_IfInteger#ChildLess,
	* UDialogGraphNode_IfInteger#ChildEqual or UDialogGraphNode_IfInteger#ChildMore property depending on the output pin's name.
	* @param Pin Output pin of this node with valid child node connected
	* @param Child Child node connected to this output pin
	*/
	virtual void AddSpecialChild(const UEdGraphPin* Pin, UGenericGraphNode* Child) override
	{
		UDialogGraphNode_IfInteger* IntegerNode = CastChecked<UDialogGraphNode_IfInteger>(GenericGraphNode);
		UDialogGraphNode* DialogChild = CastChecked<UDialogGraphNode>(Child);
		if (Pin->PinName == PinNameLess) IntegerNode->ChildLess = DialogChild;
		else if (Pin->PinName == PinNameEqual) IntegerNode->ChildEqual = DialogChild;
		else if (Pin->PinName == PinNameMore) IntegerNode->ChildMore = DialogChild;
	}
};