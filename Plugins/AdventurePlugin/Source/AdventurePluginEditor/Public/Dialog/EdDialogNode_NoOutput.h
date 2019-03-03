#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialog/EdDialogNode.h"
#include "EdDialogNode_NoOutput.generated.h"

/**
* Class representing behavior of a dialog node with one input pin but without any output pin.
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_NoOutput : public UEdDialogNode
{
	GENERATED_BODY()

public:

	UEdDialogNode_NoOutput() { }
	virtual ~UEdDialogNode_NoOutput() { }

	/**
	* Allocates default input pin for a NoOutput node.
	*/
	virtual void AllocateDefaultPins() override
	{
		CreatePin(EGPD_Input, "MultipleNodes", FName(), FName());
	}

	/**
	* Returns nullptr as this node has no output pin.
	*/
	virtual UEdGraphPin* GetOutputPin() const override
	{
		return nullptr;
	}
};