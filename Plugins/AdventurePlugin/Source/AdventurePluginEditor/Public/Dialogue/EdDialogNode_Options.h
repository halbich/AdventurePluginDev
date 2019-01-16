#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "Dialogue/EdDialogNode.h"
#include "Dialogue/SEdDialogNode_Options.h"
#include "EdDialogNode_Options.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode_Options : public UEdDialogNode
{
	GENERATED_BODY()

public:

	UEdDialogNode_Options() { }
	virtual ~UEdDialogNode_Options() { }

	virtual TSharedPtr<class SGraphNode> CreateVisualWidget() override
	{
		return SNew(SEdDialogNode_Options, this);
	}
};