#include "Dialog/Graph/DialogGraphNode.h"
#include "Dialog/Graph/DialogGraph.h"

#define LOCTEXT_NAMESPACE "DialogGraphNode"

UDialogGraphNode::UDialogGraphNode()
{
#if WITH_EDITORONLY_DATA
	CompatibleGraphType = UDialogGraph::StaticClass();
	ContextMenuCategory = NSLOCTEXT("NodeCategories", "DialogNodeCategory", "Dialog nodes");
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
}

bool UDialogGraphNode::CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
{
	return true;
}

bool UDialogGraphNode::CanRename() const
{
	return false;
}

#endif

UDialogGraph * UDialogGraphNode::GetDialogGraph() const
{
	UDialogGraph* DialogGraph = Cast<UDialogGraph>(Graph);
	if (!IsValid(DialogGraph))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "DialogGraphNode_InvalidDialogGraph", "DialogGraphNode: Parent graph is not a dialog graph"));
		return nullptr;
	}
	return DialogGraph;
}

#undef LOCTEXT_NAMESPACE