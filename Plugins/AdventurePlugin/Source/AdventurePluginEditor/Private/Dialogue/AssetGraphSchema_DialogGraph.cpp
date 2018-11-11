#include "Dialogue/AssetGraphSchema_DialogGraph.h"
#include "DialogGraphNode_EntryMain.h"
#include "GenericGraphEditor/Private/GenericGraphAssetEditor/EdNode_GenericGraphNode.h"
#include "EdGraph/EdGraph.h"


const FPinConnectionResponse UAssetGraphSchema_DialogGraph::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	FPinConnectionResponse res = Super::CanCreateConnection(A, B);
	if (res.Response == CONNECT_RESPONSE_MAKE) res.Response = CONNECT_RESPONSE_BREAK_OTHERS_A;
	return res;
}

void UAssetGraphSchema_DialogGraph::CreateDefaultNodesForGraph(UEdGraph& EdGraph) const
{
	FAssetSchemaAction_GenericGraph_NewNode Action;
	UDialogGraph* EditingGraph = CastChecked<UDialogGraph>(EdGraph.GetOuter());
	Action.NodeTemplate = NewObject<UEdNode_GenericGraphNode>(&EdGraph, GetEditorNodeType());
	Action.NodeTemplate->GenericGraphNode = NewObject<UGenericGraphNode>(Action.NodeTemplate, UDialogGraphNode_EntryMain::StaticClass());
	Action.NodeTemplate->GenericGraphNode->Graph = EditingGraph;
	EditingGraph->MainEntryPoint = Cast<UDialogGraphNode>(Action.NodeTemplate->GenericGraphNode);
	Action.PerformAction(EditingGraph->EdGraph, nullptr, FVector2D(0, 0), false);
}

TSubclassOf<UEdNode_GenericGraphNode> UAssetGraphSchema_DialogGraph::GetEditorNodeType() const
{
	return UEdDialogNode::StaticClass();
}
