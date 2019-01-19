#include "GenericGraphNode.h"
#include "GenericGraph.h"

#define LOCTEXT_NAMESPACE "GenericGraphNode"

UGenericGraphNode::UGenericGraphNode()
{
#if WITH_EDITORONLY_DATA
	CompatibleGraphType = UGenericGraph::StaticClass();

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

/*
UGenericGraphNode* UGenericGraphNode::GetFirstChildInBin(int bin) const
{
	int bins = ChildrenNodesBins.Num();
	//check(bins == GetOutputPinsCount());
	check(bins > bin);
	int32 child = ChildrenNodesBins[bin];
	if (bin + 1 < bins && ChildrenNodesBins[bin + 1] == child) return nullptr;
	return ChildrenNodes.Num() > child ? ChildrenNodes[child] : nullptr;
}
*/

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
