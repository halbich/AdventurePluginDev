#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialog/EdDialogNode.h"
#include "EdDialogNode_NoInput.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_NoInput : public UEdDialogNode
{
	GENERATED_BODY()

public:

	UEdDialogNode_NoInput() { }
	virtual ~UEdDialogNode_NoInput() { }

	virtual void AllocateDefaultPins() override
	{
		CreatePin(EGPD_Output, "MultipleNodes", FName(), FName());
	}

	virtual UEdGraphPin* GetInputPin() const override
	{
		return nullptr;
	}

	virtual UEdGraphPin* GetOutputPin() const override
	{
		return Pins[0];
	}
};