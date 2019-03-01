#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialog/EdDialogNode.h"
#include "EdDialogNode_NoInput.generated.h"

/**
* Class representing behavior of a dialog node with one output pin but without input pin.
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_NoInput : public UEdDialogNode
{
	GENERATED_BODY()

public:

	UEdDialogNode_NoInput() { }
	virtual ~UEdDialogNode_NoInput() { }

	/**
	* Allocates default output pin for a NoInput node.
	*/
	virtual void AllocateDefaultPins() override
	{
		CreatePin(EGPD_Output, "MultipleNodes", FName(), FName());
	}

	/*
	* Returns nullptr as this node has no input pin.
	*/
	virtual UEdGraphPin* GetInputPin() const override
	{
		return nullptr;
	}

	/*
	* Returns first and only output pin of this node.
	*/
	virtual UEdGraphPin* GetOutputPin() const override
	{
		return Pins[0];
	}
};