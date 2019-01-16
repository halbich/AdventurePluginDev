#pragma once

#include "CoreMinimal.h"
#include "StoryEngine/Graph/QuestGraphNode.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "GenericGraph/SEdNode_GenericGraphNode.h"

class ADVENTUREPLUGINEDITOR_API SEdQuestNode : public SEdNode_GenericGraphNode
{
public:

	virtual void Construct(const FArguments& InArgs, UEdNode_GenericGraphNode* InNode) override;

protected:

	UQuestGraphNode* QuestGraphNode;

	virtual TSharedPtr<SBoxPanel> GetMainBox() override;
	virtual FMargin GetInputPinMargin() const override;
	virtual FText GetUpperText() const override;
	virtual EVisibility GetUpperTextVisibility() const override;
};