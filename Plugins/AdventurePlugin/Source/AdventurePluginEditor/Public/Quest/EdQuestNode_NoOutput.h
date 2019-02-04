#pragma once

#include "CoreMinimal.h"
#include "Quest/EdQuestNode.h"
#include "EdQuestNode_NoOutput.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdQuestNode_NoOutput : public UEdQuestNode
{
	GENERATED_BODY()

public:

	UEdQuestNode_NoOutput() { }
	virtual ~UEdQuestNode_NoOutput() { }

	virtual void AllocateDefaultPins() override
	{
		CreatePin(EGPD_Input, "MultipleNodes", FName(), FName());
	}

	virtual UEdGraphPin* GetOutputPin() const override
	{
		return nullptr;
	}
};