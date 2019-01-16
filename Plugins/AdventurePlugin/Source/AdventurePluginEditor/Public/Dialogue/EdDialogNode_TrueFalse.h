#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialogue/EdDialogNode.h"
#include "Dialogue/SEdDialogNode_TrueFalse.h"
#include "EdDialogNode_TrueFalse.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_TrueFalse : public UEdDialogNode
{
	GENERATED_BODY()

public:

	UEdDialogNode_TrueFalse() { }
	virtual ~UEdDialogNode_TrueFalse() { }

	virtual TSharedPtr<class SGraphNode> CreateVisualWidget() override
	{
		return SNew(SEdDialogNode_TrueFalse, this);
	}
};