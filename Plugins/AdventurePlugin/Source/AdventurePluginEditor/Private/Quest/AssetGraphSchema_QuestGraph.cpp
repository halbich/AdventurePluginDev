#include "Quest/AssetGraphSchema_QuestGraph.h"
#include "Quest/EdQuestNode_NoOutput.h"
#include "QuestGraphNode_End.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "EdGraph/EdGraph.h"

UAssetGraphSchema_QuestGraph::UAssetGraphSchema_QuestGraph()
{
	EditorNodeMap.Add(UQuestGraphNode_End::StaticClass(), UEdQuestNode_NoOutput::StaticClass());
}

const FPinConnectionResponse UAssetGraphSchema_QuestGraph::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	FPinConnectionResponse res = Super::CanCreateConnection(A, B);
	return res;
}

void UAssetGraphSchema_QuestGraph::CreateDefaultNodesForGraph(UEdGraph& EdGraph) const
{
	FAssetSchemaAction_GenericGraph_NewNode Action;
	UQuestGraph* EditingGraph = CastChecked<UQuestGraph>(EdGraph.GetOuter());
	Action.NodeTemplate = NewObject<UEdNode_GenericGraphNode>(&EdGraph, GetEditorNodeType(UQuestGraphNode_End::StaticClass()));
	Action.NodeTemplate->GenericGraphNode = NewObject<UGenericGraphNode>(Action.NodeTemplate, UQuestGraphNode_End::StaticClass());

	EditingGraph->EndNode = Cast<UQuestGraphNode>(Action.NodeTemplate->GenericGraphNode);
	Action.NodeTemplate->GenericGraphNode->Graph = EditingGraph;
	Action.PerformAction(EditingGraph->EdGraph, nullptr, FVector2D(0, 0), false);
}

TSubclassOf<UEdNode_GenericGraphNode> UAssetGraphSchema_QuestGraph::GetEditorNodeType(TSubclassOf<UGenericGraphNode> RuntimeNodeType) const
{
	if (RuntimeNodeType && RuntimeNodeType->IsChildOf(UQuestGraphNode::StaticClass()))
	{
		if (const TSubclassOf<UEdNode_GenericGraphNode>* EditorNodeType = FindEditorNodeForRuntimeNode(RuntimeNodeType))
		{
			return *EditorNodeType;
		}
	}

	return UEdQuestNode::StaticClass();
}
