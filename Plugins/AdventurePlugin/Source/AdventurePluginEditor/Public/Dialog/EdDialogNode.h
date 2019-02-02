#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "Dialog/SEdDialogNode.h"
#include "EdDialogNode.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode : public UEdNode_GenericGraphNode
{
	GENERATED_BODY()

public:

	UEdDialogNode() { }
	virtual ~UEdDialogNode() { }

	virtual TSharedPtr<class SGraphNode> CreateVisualWidget() override
	{
		return SNew(SEdDialogNode, this);
	}
};