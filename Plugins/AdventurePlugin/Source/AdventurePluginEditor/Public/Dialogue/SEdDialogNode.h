#pragma once

#include "CoreMinimal.h"
#include "Dialogue/Graph/DialogGraphNode.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "GenericGraph/SEdNode_GenericGraphNode.h"

class ADVENTUREPLUGINEDITOR_API SEdDialogNode : public SEdNode_GenericGraphNode
{
public:

	virtual void Construct(const FArguments& InArgs, UEdNode_GenericGraphNode* InNode) override;

protected:

	UDialogGraphNode* DialogGraphNode;

	virtual FText GetUpperText() const override;
	virtual EVisibility GetUpperTextVisibility() const override;
	virtual FText GetLowerText() const override;
	virtual EVisibility GetLowerTextVisibility() const override;
};