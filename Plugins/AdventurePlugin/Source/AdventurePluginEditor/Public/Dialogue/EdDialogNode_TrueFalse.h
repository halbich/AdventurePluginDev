#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialogue/EdDialogNode.h"
#include "EdDialogNode_TrueFalse.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_TrueFalse : public UEdDialogNode
{
	GENERATED_BODY()

public:

	UEdDialogNode_TrueFalse() { }
	virtual ~UEdDialogNode_TrueFalse() { }

	virtual void AllocateDefaultPins() override
	{
		CreatePin(EGPD_Input, "MultipleNodes", FName(), FName());
		CreatePin(EGPD_Output, "MultipleNodes", FName(), FName("True"));
		CreatePin(EGPD_Output, "MultipleNodes", FName(), FName("False"));
	}
};