#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialog/EdDialogNode.h"
#include "Dialog/EdDialogNode_TrueFalse.h"
#include "Dialog/Graph/DialogGraphNode_IfInInventory.h"
#include "EdDialogNode_IfInInventory.generated.h"

/**
* Class representing behavior of a IfInInventory dialog node with one input pin and two output pins
* labeled "True" and "False".
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_IfInInventory : public UEdDialogNode_TrueFalse
{
	GENERATED_BODY()

public:

	UEdDialogNode_IfInInventory() { }
	virtual ~UEdDialogNode_IfInInventory() { }

	virtual void AddSpecialChild(const UEdGraphPin* Pin, UGenericGraphNode* Child) override
	{
		UDialogGraphNode_IfInInventory* TrueFalseNode = CastChecked<UDialogGraphNode_IfInInventory>(GenericGraphNode);
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