#pragma once

#include "CoreMinimal.h"
#include "Quest/EdQuestNode.h"
#include "EdQuestNode_NoOutput.generated.h"

/**
* Class representing behavior of a quest node with one input pin but without any output pin.
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdQuestNode_NoOutput : public UEdQuestNode
{
	GENERATED_BODY()

public:

	UEdQuestNode_NoOutput() { }
	virtual ~UEdQuestNode_NoOutput() { }

	/**
	* Allocates default input pin for a NoOutput node.
	*/
	virtual void AllocateDefaultPins() override
	{
		CreatePin(EGPD_Input, "MultipleNodes", FName(), FName());
	}

	/*
	* Returns nullptr as this node has no output pin.
	*/
	virtual UEdGraphPin* GetOutputPin() const override
	{
		return nullptr;
	}
};