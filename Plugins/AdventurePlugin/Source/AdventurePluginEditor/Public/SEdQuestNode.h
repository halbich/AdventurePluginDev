#pragma once

#include "CoreMinimal.h"
#include "GenericGraphEditor/Private/GenericGraphAssetEditor/SEdNode_GenericGraphNode.h"

class ADVENTUREPLUGINEDITOR_API SEdQuestNode : public SEdNode_GenericGraphNode
{
public:
	virtual void UpdateGraphNode() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
};