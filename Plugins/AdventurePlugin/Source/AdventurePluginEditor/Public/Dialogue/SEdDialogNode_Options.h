#pragma once

#include "CoreMinimal.h"
#include "Dialogue/SEdDialogNode.h"

class ADVENTUREPLUGINEDITOR_API SEdDialogNode_Options : public SEdDialogNode
{
public:

	virtual void CreatePinWidgets() override;

protected:

	virtual TSharedPtr<SBoxPanel> GetMainBox() override;
	virtual FReply IncrementOptionsCount();
	virtual FReply DecrementOptionsCount();
};