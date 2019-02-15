#include "GenericGraph.h"
#include "Engine/Engine.h"

#define LOCTEXT_NAMESPACE "GenericGraph"

UGenericGraph::UGenericGraph()
{
	NodeType = UGenericGraphNode::StaticClass();

#if WITH_EDITORONLY_DATA
	EdGraph = nullptr;
	bCanRenameNode = true;
#endif
}

UGenericGraph::~UGenericGraph()
{

}

void UGenericGraph::ClearGraph()
{
	for (int32 i = 0; i < AllNodes.Num(); ++i)
	{
		UGenericGraphNode* Node = AllNodes[i];
		if (!IsValid(Node))
		{
			continue;
		}
		Node->ParentNodes.Empty();
		Node->ChildrenNodes.Empty();
	}

	AllNodes.Empty();
	RootNodes.Empty();
}

#undef LOCTEXT_NAMESPACE
