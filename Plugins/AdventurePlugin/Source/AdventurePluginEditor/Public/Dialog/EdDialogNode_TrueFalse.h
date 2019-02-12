#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialog/EdDialogNode.h"
#include "Dialog/Graph/BaseClasses/DialogGraphNode_TrueFalse.h"
#include "EdDialogNode_TrueFalse.generated.h"

const FName PinNameTrue("True");
const FName PinNameFalse("False");

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
		CreatePin(EGPD_Output, "MultipleNodes", FName(), PinNameTrue);
		CreatePin(EGPD_Output, "MultipleNodes", FName(), PinNameFalse);
	}

	virtual void AddSpecialChild(const UEdGraphPin* Pin, UGenericGraphNode* Child) override
	{
		UDialogGraphNode_TrueFalse* TrueFalseNode = CastChecked<UDialogGraphNode_TrueFalse>(GenericGraphNode);
		UDialogGraphNode* DialogChild = CastChecked<UDialogGraphNode>(Child);
		if (Pin->PinName == PinNameTrue) TrueFalseNode->ChildTrue = DialogChild;
		else if (Pin->PinName == PinNameFalse) TrueFalseNode->ChildFalse = DialogChild;
	}
};