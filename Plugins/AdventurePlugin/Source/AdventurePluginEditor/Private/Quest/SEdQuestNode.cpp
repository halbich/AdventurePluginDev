#include "Quest/SEdQuestNode.h"
#include "SCommentBubble.h"
#include "SlateOptMacros.h"
#include "SGraphPin.h"
#include "SWrapTitleBox.h"

void SEdQuestNode::Construct(const FArguments& InArgs, UEdNode_GenericGraphNode* InNode)
{
	QuestGraphNode = Cast<UQuestGraphNode>(InNode->GenericGraphNode);

	SEdNode_GenericGraphNode::Construct(InArgs, InNode);
}

FText SEdQuestNode::GetUpperText() const
{
#if WITH_EDITORONLY_DATA
	if (QuestGraphNode)
	{
		return QuestGraphNode->Location;
	}
	else
#endif
	{
		return FText();
	}
}

EVisibility SEdQuestNode::GetUpperTextVisibility() const
{
#if WITH_EDITORONLY_DATA
	if (QuestGraphNode && !QuestGraphNode->Location.IsEmpty())
	{
		return EVisibility::Visible;
	}
	else
#endif
	{
		return EVisibility::Collapsed;
	}
}