#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialog/EdDialogNode.h"
#include "Dialog/Graph/BaseClasses/DialogGraphNode_TrueFalse.h"
#include "EdDialogNode_TrueFalse.generated.h"

const FName PinNameTrue("True");
const FName PinNameFalse("False");

/**
* Class representing behavior of a dialog node with one input pin and two output pins
* labeled "True" and "False".
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_TrueFalse : public UEdDialogNode
{
	GENERATED_BODY()

public:

	UEdDialogNode_TrueFalse() { }
	virtual ~UEdDialogNode_TrueFalse() { }

	/**
	* Allocates default pins for a TrueFalse node, one input and two outputs.
	*/
	virtual void AllocateDefaultPins() override
	{
		CreatePin(EGPD_Input, "MultipleNodes", FName(), FName());
		CreatePin(EGPD_Output, "MultipleNodes", FName(), PinNameTrue);
		CreatePin(EGPD_Output, "MultipleNodes", FName(), PinNameFalse);
	}

	/**
	* This method is called when the graph is rebuilding, for every output pin and
	* the node connected to it. It sets the child node to the parent's UDialogGraphNode_TrueFalse#ChildTrue
	* or UDialogGraphNode_TrueFalse#ChildFalse property depending on the output pin's name.
	* @param Pin Output pin of this node with valid child node connected
	* @param Child Child node connected to this output pin
	*/
	virtual void AddSpecialChild(const UEdGraphPin* Pin, UGenericGraphNode* Child) override
	{
		UDialogGraphNode_TrueFalse* TrueFalseNode = CastChecked<UDialogGraphNode_TrueFalse>(GenericGraphNode);
		UDialogGraphNode* DialogChild = CastChecked<UDialogGraphNode>(Child);
		if (Pin->PinName == PinNameTrue)
		{
			TrueFalseNode->ChildTrue = DialogChild;
		}
		else if (Pin->PinName == PinNameFalse)
		{
			TrueFalseNode->ChildFalse = DialogChild;
		}
	}
};