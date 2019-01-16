#include "StoryEngine/SEdQuestNode.h"
#include "SCommentBubble.h"
#include "SlateOptMacros.h"
#include "GraphEditorSettings.h"
#include "SGraphPin.h"
#include "SWrapTitleBox.h"

void SEdQuestNode::Construct(const FArguments& InArgs, UEdNode_GenericGraphNode* InNode)
{
	QuestGraphNode = Cast<UQuestGraphNode>(InNode->GenericGraphNode);

	SEdNode_GenericGraphNode::Construct(InArgs, InNode);
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedPtr<SBoxPanel> SEdQuestNode::GetMainBox()
{
	const FMargin NodePadding = FMargin(2.0f);

	return SNew(SHorizontalBox)
	
	// INPUT PIN AREA
	+ SHorizontalBox::Slot()
	.AutoWidth()
	[
		SNew(SBox)
		.MinDesiredWidth(20.0f)
		[
			SAssignNew(LeftNodeBox, SVerticalBox)
		]
	]
	
	// STATE NAME AREA
	+ SHorizontalBox::Slot()
	.Padding(FMargin(NodePadding.Left, 0.0f, NodePadding.Right, 0.0f))
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.VAlign(VAlign_Center)
		.Padding(0.0f, 20.0f)
		[
			GetNodeBody().ToSharedRef()
		]
	]
	
	// OUTPUT PIN AREA
	+ SHorizontalBox::Slot()
	.AutoWidth()
	[
		SNew(SBox)
		.MinDesiredWidth(20.0f)
		[
			SAssignNew(RightNodeBox, SVerticalBox)
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(0.0f, 10.0f)
			.FillHeight(1.0f)
			[
				SAssignNew(OutputPinBox, SHorizontalBox)
			]
		]		
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FMargin SEdQuestNode::GetInputPinMargin() const
{
	return FMargin(0.0f, 10.0f);
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