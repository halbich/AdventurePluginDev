#include "DialogGraphNode.h"
#include "DialogGraph.h"

#define LOCTEXT_NAMESPACE "DialogGraphNode"

UDialogGraphNode::UDialogGraphNode()
{
	DialogText = LOCTEXT("DefaultDialog", "<Insert something clever>");
#if WITH_EDITORONLY_DATA
	CompatibleGraphType = UDialogGraph::StaticClass();
	//BackgroundColor = FLinearColor::Red;
#endif
}

UDialogGraphNode::~UDialogGraphNode()
{
}

FText UDialogGraphNode::GetDescription_Implementation() const
{
	return LOCTEXT("NodeDesc", "Dialog Graph Node");
}

#if WITH_EDITOR

void UDialogGraphNode::SetNodeTitle(const FText & NewTitle)
{
	//DialogText = NewTitle;
}

bool UDialogGraphNode::CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
{
	return true;
}

#endif

#undef LOCTEXT_NAMESPACE