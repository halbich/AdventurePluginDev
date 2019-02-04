#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "EdQuestNode.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdQuestNode : public UEdNode_GenericGraphNode
{
	GENERATED_BODY()

public:

	UEdQuestNode() { }
	virtual ~UEdQuestNode() { }

	virtual TSharedPtr<class SGraphNode> CreateVisualWidget() override;
};