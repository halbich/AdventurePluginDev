/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#include "GenericGraph/SEdNode_GenericGraphNode.h"
#include "GenericGraph/Colors_GenericGraph.h"
#include "GenericGraph/GenericGraph.h"
#include "SLevelOfDetailBranchNode.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "SCommentBubble.h"
#include "SlateOptMacros.h"
#include "SGraphPin.h"
#include "SWrapTitleBox.h"
#include "GraphEditorSettings.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"

#define LOCTEXT_NAMESPACE "EdNode_GenericGraph"

void SEdNode_GenericGraphNode::Construct(const FArguments& InArgs, UEdNode_GenericGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
	InNode->SEdNode = this;
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SEdNode_GenericGraphNode::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	// Reset variables that are going to be exposed, in case we are refreshing an already setup node.
	RightNodeBox.Reset();
	LeftNodeBox.Reset();
	TopNodeBox.Reset();
	BottomNodeBox.Reset();

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
			.Padding(0.0f)
			.BorderBackgroundColor(this, &SEdNode_GenericGraphNode::GetBorderBackgroundColor)
			[
				SNew(SOverlay)

				// Pins and node details
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					GetMainBox().ToSharedRef()
				]
			]
		];

	// Create comment bubble
	TSharedPtr<SCommentBubble> CommentBubble;
	const FSlateColor CommentColor = GetDefault<UGraphEditorSettings>()->DefaultCommentNodeTitleColor;

	SAssignNew(CommentBubble, SCommentBubble)
		.GraphNode(GraphNode)
		.Text(this, &SGraphNode::GetNodeComment)
		.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
		.ColorAndOpacity(CommentColor)
		.AllowPinning(true)
		.EnableTitleBarBubble(true)
		.EnableBubbleCtrls(true)
		.GraphLOD(this, &SGraphNode::GetCurrentLOD)
		.IsGraphNodeHovered(this, &SGraphNode::IsHovered);

	GetOrAddSlot(ENodeZone::TopCenter)
		.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
		.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
		.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
		.VAlign(VAlign_Top)
		[
			CommentBubble.ToSharedRef()
		];

	ErrorReporting->SetError(ErrorMsg);
	CreatePinWidgets();
}

TSharedPtr<SBoxPanel> SEdNode_GenericGraphNode::GetMainBox()
{
	bool horizontal = IsGraphHorizontal();
	float pinWidth = horizontal ? 20 : 5;
	float pinHeight = horizontal ? 15 : 20;
	float paddingVertical = 5;
	float paddingHorizontal = 10;

	return SNew(SHorizontalBox)

	+ SHorizontalBox::Slot()
	.AutoWidth()
	[
		SNew(SBox)
		.MinDesiredWidth(pinWidth)
		.Padding(FMargin(0, paddingVertical))
		[
			SAssignNew(LeftNodeBox, SVerticalBox)
		]
	]

	+ SHorizontalBox::Slot()
	.AutoWidth()
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBox)
			.MinDesiredHeight(pinHeight)
			.Padding(FMargin(paddingHorizontal, 0))
			[
				SAssignNew(TopNodeBox, SHorizontalBox)
			]
		]

		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		[
			GetNodeBody().ToSharedRef()
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBox)
			.MinDesiredHeight(pinHeight)
			.Padding(FMargin(paddingHorizontal, 0))
			[
				SAssignNew(BottomNodeBox, SHorizontalBox)
			]
		]
	]

	+ SHorizontalBox::Slot()
	.AutoWidth()
	[
		SNew(SBox)
		.MinDesiredWidth(pinWidth)
		.Padding(FMargin(0, paddingVertical))
		[
			SAssignNew(RightNodeBox, SVerticalBox)
		]
	];
}

TSharedPtr<SBorder> SEdNode_GenericGraphNode::GetNodeBody()
{
	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	return SAssignNew(NodeBody, SBorder)
	.BorderImage(FEditorStyle::GetBrush("BTEditor.Graph.BTNode.Body"))
	.BorderBackgroundColor(this, &SEdNode_GenericGraphNode::GetBackgroundColor)
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Center)
	.Visibility(EVisibility::SelfHitTestInvisible)
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					// POPUP ERROR MESSAGE
					SAssignNew(ErrorReporting, SErrorText)
					.BackgroundColor(this, &SEdNode_GenericGraphNode::GetErrorColor)
					.ToolTipText(this, &SEdNode_GenericGraphNode::GetErrorMsgToolTip)
				]
	
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.Padding(FMargin(4.0f, 0.0f, 4.0f, 0.0f))
					.MaxWidth(250.0f)
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(STextBlock)
							.Text(this, &SEdNode_GenericGraphNode::GetUpperText)
							.Visibility(this, &SEdNode_GenericGraphNode::GetUpperTextVisibility)
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SAssignNew(InlineEditableText, SWrapTitleBox)
							.Style(FEditorStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
							.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
							.OnVerifyTextChanged(this, &SEdNode_GenericGraphNode::OnVerifyNameTextChanged)
							.OnTextCommitted(this, &SEdNode_GenericGraphNode::OnNameTextCommited)
							.IsReadOnly(this, &SEdNode_GenericGraphNode::IsNameReadOnly)
							.IsSelected(this, &SEdNode_GenericGraphNode::IsSelectedExclusively)
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							NodeTitle.ToSharedRef()
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(STextBlock)
							.Text(this, &SEdNode_GenericGraphNode::GetLowerText)
							.Visibility(this, &SEdNode_GenericGraphNode::GetLowerTextVisibility)
						]
					]
				]
			]
		]
	];
}

void SEdNode_GenericGraphNode::CreatePinWidgets()
{
	UEdNode_GenericGraphNode* StateNode = CastChecked<UEdNode_GenericGraphNode>(GraphNode);

	for (int32 PinIdx = 0; PinIdx < StateNode->Pins.Num(); PinIdx++)
	{
		UEdGraphPin* MyPin = StateNode->Pins[PinIdx];
		if (!MyPin->bHidden)
		{
			TSharedPtr<SGraphPin> NewPin = SNew(SGenericGraphPin, MyPin);
			AddPin(NewPin.ToSharedRef());
		}
	}
}

void SEdNode_GenericGraphNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));

	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();
	const bool bAdvancedParameter = PinObj && PinObj->bAdvancedView;
	if (bAdvancedParameter)
	{
		PinToAdd->SetVisibility(TAttribute<EVisibility>(PinToAdd, &SGraphPin::IsPinVisibleAsAdvanced));
	}

	if (PinToAdd->GetDirection() == EEdGraphPinDirection::EGPD_Input)
	{
		if (IsGraphHorizontal()) AddToVerticalBox(LeftNodeBox, PinToAdd);
		else AddToHorizontalBox(TopNodeBox, PinToAdd);
		InputPins.Add(PinToAdd);
	}
	else // Direction == EEdGraphPinDirection::EGPD_Output
	{
		if (IsGraphHorizontal()) AddToVerticalBox(RightNodeBox, PinToAdd);
		else AddToHorizontalBox(BottomNodeBox, PinToAdd);
		OutputPins.Add(PinToAdd);
	}
}

void SEdNode_GenericGraphNode::AddToHorizontalBox(TSharedPtr<SHorizontalBox> Box, const TSharedRef<SGraphPin>& PinToAdd)
{
	Box->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.FillWidth(1.0f)
		[
			PinToAdd
		];
}

void SEdNode_GenericGraphNode::AddToVerticalBox(TSharedPtr<SVerticalBox> Box, const TSharedRef<SGraphPin>& PinToAdd)
{
	Box->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.FillHeight(1.0f)
		[
			PinToAdd
		];
}

bool SEdNode_GenericGraphNode::IsNameReadOnly() const
{
	UEdNode_GenericGraphNode* EdNode_Node = Cast<UEdNode_GenericGraphNode>(GraphNode);
	check(EdNode_Node != nullptr);

	UGenericGraphNode* Node = EdNode_Node->GenericGraphNode;
	UGenericGraph* GenericGraph = Node->Graph;
	check(GenericGraph != nullptr);

	return !GenericGraph->bCanRenameNode || !Node->CanRename() || SGraphNode::IsNameReadOnly();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SEdNode_GenericGraphNode::OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo)
{
	SGraphNode::OnNameTextCommited(InText, CommitInfo);

	UEdNode_GenericGraphNode* MyNode = CastChecked<UEdNode_GenericGraphNode>(GraphNode);

	if (MyNode != nullptr && MyNode->GenericGraphNode != nullptr)
	{
		const FScopedTransaction Transaction(LOCTEXT("GenericGraphEditorRenameNode", "Generic Graph Editor: Rename Node"));
		MyNode->Modify();
		MyNode->GenericGraphNode->Modify();
		MyNode->GenericGraphNode->SetNodeTitle(InText);
		UpdateGraphNode();
	}
}

FSlateColor SEdNode_GenericGraphNode::GetBorderBackgroundColor() const
{
	UEdNode_GenericGraphNode* MyNode = CastChecked<UEdNode_GenericGraphNode>(GraphNode);
	return MyNode ? MyNode->GetBackgroundColor() : GenericGraphColors::NodeBorder::HighlightAbortRange0;
}

FSlateColor SEdNode_GenericGraphNode::GetBackgroundColor() const
{
	return GenericGraphColors::NodeBody::Default;
}

#undef LOCTEXT_NAMESPACE
