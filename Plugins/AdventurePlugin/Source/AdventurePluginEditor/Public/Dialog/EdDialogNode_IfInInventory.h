#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialog/EdDialogNode.h"
#include "Dialog/EdDialogNode_TrueFalse.h"
#include "Dialog/Graph/DialogGraphNode_IfInInventory.h"
#include "EdDialogNode_IfInInventory.generated.h"

/**
* Class representing behavior of a UDialogGraphNode_IfInInventory dialog node with one input pin and two output pins
* labeled "True" and "False".
* Register this editor only for runtime nodes inheriting from UDialogGraphNode_IfInInventory.
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_IfInInventory : public UEdDialogNode_TrueFalse
{
	GENERATED_BODY()

public:

	UEdDialogNode_IfInInventory() { }
	virtual ~UEdDialogNode_IfInInventory() { }

	/**
	* This method is called when the graph is rebuilding, for every output pin and
	* the node connected to it. It sets the child node to the parent's UDialogGraphNode_IfInInventory#ChildTrue
	* or UDialogGraphNode_IfInInventory#ChildFalse property depending on the output pin's name.
	* @param Pin Output pin of this node with valid child node connected
	* @param Child Child node connected to this output pin
	*/
	virtual void AddSpecialChild(const UEdGraphPin* Pin, UGenericGraphNode* Child) override
	{
		UDialogGraphNode_IfInInventory* TrueFalseNode = CastChecked<UDialogGraphNode_IfInInventory>(GenericGraphNode);
		UDialogGraphNode* DialogChild = CastChecked<UDialogGraphNode>(Child);
		if (!IsValid(TrueFalseNode) || !IsValid(DialogChild))
		{
			check(TrueFalseNode && DialogChild && "Invalid inputs for UEdDialogNode_IfInInventory.");
			return;
		}
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