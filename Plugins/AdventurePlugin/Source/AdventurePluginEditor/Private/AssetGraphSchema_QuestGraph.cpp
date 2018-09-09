#include "AssetGraphSchema_QuestGraph.h"
#include "QuestGraphNode_End.h"
#include "GenericGraphEditor/Private/GenericGraphAssetEditor/EdNode_GenericGraphNode.h"
#include "EdGraph/EdGraph.h"

const FPinConnectionResponse UAssetGraphSchema_QuestGraph::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	FPinConnectionResponse res = Super::CanCreateConnection(A, B);
	//if (res.Response == CONNECT_RESPONSE_MAKE) res.Response = CONNECT_RESPONSE_BREAK_OTHERS_A;
	return res;
}

void UAssetGraphSchema_QuestGraph::CreateDefaultNodesForGraph(UEdGraph& EdGraph) const
{
	FAssetSchemaAction_GenericGraph_NewNode Action;
	UGenericGraph* EditingGraph = CastChecked<UGenericGraph>(EdGraph.GetOuter());
	Action.NodeTemplate = NewObject<UEdNode_GenericGraphNode>(&EdGraph, GetEditorNodeType());
	Action.NodeTemplate->GenericGraphNode = NewObject<UGenericGraphNode>(Action.NodeTemplate, UQuestGraphNode_End::StaticClass());
	Action.NodeTemplate->GenericGraphNode->Graph = EditingGraph;
	Action.PerformAction(EditingGraph->EdGraph, nullptr, FVector2D(0, 0), false);
}

TSubclassOf<UEdNode_GenericGraphNode> UAssetGraphSchema_QuestGraph::GetEditorNodeType() const
{
	return UEdQuestNode::StaticClass();
}
