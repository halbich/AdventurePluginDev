/* This file is based on a third party plugin called Generic Graph Editor, created by jinyuliao, which is distributed under MIT license and is available here: https://github.com/jinyuliao/GenericGraph */

#include "GenericGraphNode.h"
#include "GenericGraph.h"

#define LOCTEXT_NAMESPACE "GenericGraphNode"

UGenericGraphNode::UGenericGraphNode()
{
#if WITH_EDITORONLY_DATA
	CompatibleGraphType = UGenericGraph::StaticClass();
	ContextMenuCategory = NSLOCTEXT("NodeCategories", "GenericNodeCategory", "Generic nodes");
	BackgroundColor = FLinearColor::Black;
#endif
}

UGenericGraphNode::~UGenericGraphNode()
{

}

FText UGenericGraphNode::GetDescription_Implementation() const
{
	return LOCTEXT("NodeDesc", "Generic Graph Node");
}


#if WITH_EDITOR

FLinearColor UGenericGraphNode::GetBackgroundColor() const
{
	return BackgroundColor;
}

FText UGenericGraphNode::GetNodeTitle() const
{
	return NodeTitle.IsEmpty() ? GetDescription() : NodeTitle;
}

void UGenericGraphNode::SetNodeTitle(const FText& NewTitle)
{
	NodeTitle = NewTitle;
}

bool UGenericGraphNode::CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
{
	return true;
}

bool UGenericGraphNode::CanAdd() const
{
	return true;
}

bool UGenericGraphNode::CanDelete() const
{
	return true;
}

bool UGenericGraphNode::CanDuplicate() const
{
	return true;
}

bool UGenericGraphNode::CanRename() const
{
	return true;
}

#endif

bool UGenericGraphNode::IsLeafNode() const
{
	return ChildrenNodes.Num() == 0;
}

UGenericGraph* UGenericGraphNode::GetGraph() const
{
	return Graph;
}

#undef LOCTEXT_NAMESPACE
