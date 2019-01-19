#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialogue/EdDialogNode.h"
#include "EdDialogNode_LessEqualMore.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_LessEqualMore : public UEdDialogNode
{
	GENERATED_BODY()

public:

	UEdDialogNode_LessEqualMore() { }
	virtual ~UEdDialogNode_LessEqualMore() { }

	virtual void AllocateDefaultPins() override
	{
		CreatePin(EGPD_Input, "MultipleNodes", FName(), FName());
		CreatePin(EGPD_Output, "MultipleNodes", FName(), FName("<"));
		CreatePin(EGPD_Output, "MultipleNodes", FName(), FName("="));
		CreatePin(EGPD_Output, "MultipleNodes", FName(), FName(">"));
	}
};