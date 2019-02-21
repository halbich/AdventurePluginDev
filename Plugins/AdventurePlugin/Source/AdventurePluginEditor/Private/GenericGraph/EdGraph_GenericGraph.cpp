#include "GenericGraph/EdGraph_GenericGraph.h"
#include "GenericGraph/GenericGraph.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "EdGraph/EdGraphPin.h"

UEdGraph_GenericGraph::UEdGraph_GenericGraph()
{

}

UEdGraph_GenericGraph::~UEdGraph_GenericGraph()
{

}

void UEdGraph_GenericGraph::RebuildGenericGraph()
{
	UGenericGraph* Graph = GetGenericGraph();

	Clear();

	for (int32 i = 0; i < Nodes.Num(); ++i)
	{
		if (UEdNode_GenericGraphNode* EdNode = Cast<UEdNode_GenericGraphNode>(Nodes[i]))
		{
			if (EdNode->GenericGraphNode == nullptr) continue;

			UGenericGraphNode* GenericGraphNode = EdNode->GenericGraphNode;

			NodeMap.Add(GenericGraphNode, EdNode);

			Graph->AllNodes.Add(GenericGraphNode);

			GenericGraphNode->NodeGuid = EdNode->NodeGuid;

			for (int32 PinIdx = 0; PinIdx < EdNode->Pins.Num(); ++PinIdx)
			{
				UEdGraphPin* Pin = EdNode->Pins[PinIdx];

				if (Pin->Direction != EEdGraphPinDirection::EGPD_Output) continue;

				//GenericGraphNode->ChildrenNodesBins.Add(GenericGraphNode->ChildrenNodes.Num());

				for (int32 LinkToIdx = 0; LinkToIdx < Pin->LinkedTo.Num(); ++LinkToIdx)
				{
					UGenericGraphNode* ChildNode = nullptr;
					if (UEdNode_GenericGraphNode* EdNode_Child = Cast<UEdNode_GenericGraphNode>(Pin->LinkedTo[LinkToIdx]->GetOwningNode()))
					{
						ChildNode = EdNode_Child->GenericGraphNode;
					}

					if (ChildNode != nullptr)
					{
						GenericGraphNode->ChildrenNodes.Add(ChildNode);
						ChildNode->ParentNodes.Add(GenericGraphNode);
						EdNode->AddSpecialChild(Pin, ChildNode);
					}
				}
			}
		}
	}

	for (int32 i = 0; i < Graph->AllNodes.Num(); ++i)
	{
		UGenericGraphNode* Node = Graph->AllNodes[i];
		if (Node->ParentNodes.Num() == 0)
		{
			Graph->RootNodes.Add(Node);
		}

		Node->Graph = Graph;
		Node->Rename(nullptr, Graph, REN_DontCreateRedirectors | REN_DoNotDirty);
	}

	Graph->RootNodes.Sort([&](const UGenericGraphNode& L, const UGenericGraphNode& R)
	{
		UEdNode_GenericGraphNode* EdNode_LNode = NodeMap[&L];
		UEdNode_GenericGraphNode* EdNode_RNode = NodeMap[&R];
		return EdNode_LNode->NodePosX < EdNode_RNode->NodePosX;
	});
}

UGenericGraph* UEdGraph_GenericGraph::GetGenericGraph() const
{
	return CastChecked<UGenericGraph>(GetOuter());
}

bool UEdGraph_GenericGraph::Modify(bool bAlwaysMarkDirty /*= true*/)
{
	bool Rtn = Super::Modify(bAlwaysMarkDirty);

	GetGenericGraph()->Modify();

	for (int32 i = 0; i < Nodes.Num(); ++i)
	{
		Nodes[i]->Modify();
	}

	return Rtn;
}

void UEdGraph_GenericGraph::Clear()
{
	UGenericGraph* Graph = GetGenericGraph();

	Graph->ClearGraph();
	NodeMap.Reset();

	for (int32 i = 0; i < Nodes.Num(); ++i)
	{
		if (UEdNode_GenericGraphNode* EdNode = Cast<UEdNode_GenericGraphNode>(Nodes[i]))
		{
			UGenericGraphNode* GenericGraphNode = EdNode->GenericGraphNode;
			GenericGraphNode->ParentNodes.Reset();
			GenericGraphNode->ChildrenNodes.Reset();
			//GenericGraphNode->ChildrenNodesBins.Reset();
			GenericGraphNode->ResetSpecialChildren();
		}
	}
}

void UEdGraph_GenericGraph::PostEditUndo()
{
	Super::PostEditUndo();

	NotifyGraphChanged();
}

