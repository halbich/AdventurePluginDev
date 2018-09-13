#pragma once

#include "CoreMinimal.h"
#include "GenericGraphEditor/Private/GenericGraphAssetEditor/EdNode_GenericGraphNode.h"
#include "EdDialogNode.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdDialogNode : public UEdNode_GenericGraphNode
{
	GENERATED_BODY()

public:

	UEdDialogNode() { }
	virtual ~UEdDialogNode() { }

	virtual TSharedPtr<class SGraphNode> CreateVisualWidget() override;
};