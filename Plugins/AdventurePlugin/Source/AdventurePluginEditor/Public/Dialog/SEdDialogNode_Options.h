#pragma once

#include "CoreMinimal.h"
#include "Dialog/SEdDialogNode.h"

class ADVENTUREPLUGINEDITOR_API SEdDialogNode_Options : public SEdDialogNode
{
public:

	virtual void CreatePinWidgets() override;

protected:

	virtual TSharedPtr<SBorder> GetNodeBody() override;
	virtual FReply IncrementOptionsCount();
	virtual FReply DecrementOptionsCount();
};