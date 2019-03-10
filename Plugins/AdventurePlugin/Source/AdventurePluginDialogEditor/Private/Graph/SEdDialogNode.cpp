#include "Graph/SEdDialogNode.h"
#include "SCommentBubble.h"
#include "SlateOptMacros.h"
#include "GraphEditorSettings.h"
#include "SGraphPin.h"
#include "STextBlock.h"

void SEdDialogNode::Construct(const FArguments& InArgs, UEdNode_GenericGraphNode* InNode)
{
	DialogGraphNode = Cast<UDialogGraphNode>(InNode->GenericGraphNode);

	SEdNode_GenericGraphNode::Construct(InArgs, InNode);
}

FText SEdDialogNode::GetUpperText() const
{
	return DialogGraphNode ? FText::FromName(DialogGraphNode->Id) : FText();
}

EVisibility SEdDialogNode::GetUpperTextVisibility() const
{
	return DialogGraphNode && !DialogGraphNode->Id.IsNone() ? EVisibility::Visible : EVisibility::Collapsed;
}

FText SEdDialogNode::GetLowerText() const
{
#if WITH_EDITORONLY_DATA
	if (DialogGraphNode)
	{
		return DialogGraphNode->Note;
	}
	else
#endif
	{
		return FText();
	}
}

EVisibility SEdDialogNode::GetLowerTextVisibility() const
{
#if WITH_EDITORONLY_DATA
	if (DialogGraphNode && !DialogGraphNode->Note.IsEmpty())
	{
		return EVisibility::Visible;
	}
	else
#endif
	{
		return EVisibility::Collapsed;
	}
}