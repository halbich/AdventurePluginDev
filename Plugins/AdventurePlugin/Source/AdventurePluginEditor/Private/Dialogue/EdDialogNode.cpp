#include "Dialogue/EdDialogNode.h"
#include "Slate.h"
#include "Dialogue/SEdDialogNode.h"

TSharedPtr<class SGraphNode> UEdDialogNode::CreateVisualWidget()
{
	return SNew(SEdDialogNode, this);
}