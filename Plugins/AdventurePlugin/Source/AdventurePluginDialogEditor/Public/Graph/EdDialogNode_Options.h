#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Graph/EdDialogNode.h"
#include "Graph/SEdDialogNode_Options.h"
#include "Dialog/Graph/DialogGraphNode_Options.h"
#include "EdDialogNode_Options.generated.h"

const FName PinNameFallback("FB");

/**
* Class representing behavior of a dialog node with one input pin and variable number of output pins,
* first of which is labeled "FB" (fallback) and others are labeled "1", "2" and so on.
*/
UCLASS()
class ADVENTUREPLUGINDIALOGEDITOR_API UEdDialogNode_Options : public UEdDialogNode
{
	GENERATED_BODY()

public:

	UEdDialogNode_Options() { }
	virtual ~UEdDialogNode_Options() { }

	/**
	* Allocates default pins for a Options node, one input, fallback output and first regular output.
	*/
	virtual void AllocateDefaultPins() override
	{
		CreatePin(EGPD_Input, "MultipleNodes", FName(), FName());
		CreatePin(EGPD_Output, "MultipleNodes", FName(), PinNameFallback);
		CreatePin(EGPD_Output, "MultipleNodes", FName(), FName("1"));
	}

	/**
	* This method is called when the graph is rebuilding, for every output pin and
	* the node connected to it. It sets the child node to the parent's UDialogGraphNode_Options#ChildFallback
	* property if the output pin's name is "FB", otherwise it puts the child node to
	* the parent's UDialogGraphNode_Options#ChildOptions map, with number of the output pin as a key.
	* @param Pin Output pin of this node with valid child node connected
	* @param Child Child node connected to this output pin
	*/
	virtual void AddSpecialChild(const UEdGraphPin* Pin, UGenericGraphNode* Child) override
	{
		UDialogGraphNode_Options* OptionsNode = CastChecked<UDialogGraphNode_Options>(GenericGraphNode);
		UDialogGraphNode* DialogChild = CastChecked<UDialogGraphNode>(Child);
		if (!IsValid(OptionsNode) || !IsValid(DialogChild))
		{
			check(false && "Invalid inputs for the EDDialogNode_Options");
			return;
		}
		if (Pin->PinName == PinNameFallback)
		{
			OptionsNode->ChildFallback = DialogChild;
		}
		else
		{
			FString NumString = Pin->PinName.GetPlainNameString();
			if (NumString.IsNumeric())
			{
				int32 Number = FCString::Atoi(*NumString);
				check(Number > 0 && Number <= (int32)OptionsNode->ChoiceCount);
				OptionsNode->ChildOptions.Add(Number - 1, DialogChild);
			}
		}
	}

	virtual TSharedPtr<class SGraphNode> CreateVisualWidget() override
	{
		return SNew(SEdDialogNode_Options, this);
	}
};