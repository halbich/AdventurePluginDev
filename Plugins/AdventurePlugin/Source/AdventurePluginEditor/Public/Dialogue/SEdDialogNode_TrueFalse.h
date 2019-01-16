#pragma once

#include "CoreMinimal.h"
#include "Dialogue/SEdDialogNode.h"

class ADVENTUREPLUGINEDITOR_API SEdDialogNode_TrueFalse : public SEdDialogNode
{
public:
	virtual void CreatePinWidgets() override;
};