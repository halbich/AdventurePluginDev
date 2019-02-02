#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialog/EdDialogNode.h"
#include "Dialog/Graph/DialogGraphNode_IfInteger.h"
#include "EdDialogNode_LessEqualMore.generated.h"

const FName PinNameLess("<");
const FName PinNameEqual("=");
const FName PinNameMore(">");

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
		CreatePin(EGPD_Output, "MultipleNodes", FName(), PinNameLess);
		CreatePin(EGPD_Output, "MultipleNodes", FName(), PinNameEqual);
		CreatePin(EGPD_Output, "MultipleNodes", FName(), PinNameMore);
	}

	virtual void AddSpecialChild(const UEdGraphPin* Pin, UGenericGraphNode* Child) override
	{
		auto IntegerNode = CastChecked<UDialogGraphNode_IfInteger>(GenericGraphNode);
		auto DialogChild = CastChecked<UDialogGraphNode>(Child);
		if (Pin->PinName == PinNameLess) IntegerNode->ChildLess = DialogChild;
		else if (Pin->PinName == PinNameEqual) IntegerNode->ChildEqual = DialogChild;
		else if (Pin->PinName == PinNameMore) IntegerNode->ChildMore = DialogChild;
	}
};