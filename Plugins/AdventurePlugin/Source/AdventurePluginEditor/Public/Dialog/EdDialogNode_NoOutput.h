#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialog/EdDialogNode.h"
#include "EdDialogNode_NoOutput.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_NoOutput : public UEdDialogNode
{
	GENERATED_BODY()

public:

	UEdDialogNode_NoOutput() { }
	virtual ~UEdDialogNode_NoOutput() { }

	virtual void AllocateDefaultPins() override
	{
		CreatePin(EGPD_Input, "MultipleNodes", FName(), FName());
	}

	virtual UEdGraphPin* GetOutputPin() const override
	{
		return nullptr;
	}
};