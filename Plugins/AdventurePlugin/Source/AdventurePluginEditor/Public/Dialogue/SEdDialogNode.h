#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/SEdNode_GenericGraphNode.h"

class ADVENTUREPLUGINEDITOR_API SEdDialogNode : public SEdNode_GenericGraphNode
{
public:
	virtual void UpdateGraphNode() override;
};