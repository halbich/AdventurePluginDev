#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialog/EdDialogNode.h"
#include "Dialog/SEdDialogNode_Options.h"
#include "Dialog/Graph/DialogGraphNode_Options.h"
#include "EdDialogNode_Options.generated.h"

const FName PinNameFallback("FB");

UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_Options : public UEdDialogNode
{
	GENERATED_BODY()

public:

	UEdDialogNode_Options() { }
	virtual ~UEdDialogNode_Options() { }

	virtual void AllocateDefaultPins() override
	{
		CreatePin(EGPD_Input, "MultipleNodes", FName(), FName());
		CreatePin(EGPD_Output, "MultipleNodes", FName(), PinNameFallback);
		CreatePin(EGPD_Output, "MultipleNodes", FName(), FName("1"));
	}

	virtual void AddSpecialChild(const UEdGraphPin* Pin, UGenericGraphNode* Child) override
	{
		UDialogGraphNode_Options* OptionsNode = CastChecked<UDialogGraphNode_Options>(GenericGraphNode);
		UDialogGraphNode* DialogChild = CastChecked<UDialogGraphNode>(Child);
		if (Pin->PinName == PinNameFallback) OptionsNode->ChildFallback = DialogChild;
		else
		{
			FString NumString = Pin->PinName.GetPlainNameString();
			if (NumString.IsNumeric())
			{
				int32 Number = FCString::Atoi(*NumString);
				check(Number > 0 && Number <= (int32)OptionsNode->ChoiceCount);
				OptionsNode->ChildOptions.Add(Number - 1, DialogChild);
			}
		}
	}

	virtual TSharedPtr<class SGraphNode> CreateVisualWidget() override
	{
		return SNew(SEdDialogNode_Options, this);
	}
};