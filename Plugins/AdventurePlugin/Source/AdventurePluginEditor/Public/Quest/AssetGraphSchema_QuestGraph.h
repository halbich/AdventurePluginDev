#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/AssetGraphSchema_GenericGraph.h"
#include "Quest/Graph/QuestGraphNode.h"
#include "EdQuestNode.h"
#include "AssetGraphSchema_QuestGraph.generated.h"

/**
* Graph schema for UQuestGraph graph
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UAssetGraphSchema_QuestGraph : public UAssetGraphSchema_GenericGraph
{
	GENERATED_BODY()

public:

	UAssetGraphSchema_QuestGraph();

	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

	/**
	* Populates new graph with any default nodes. In this case, adds End node.
	* @param	Graph	Graph to add the default nodes to
	*/
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;

	virtual TSubclassOf<UEdNode_GenericGraphNode> GetEditorNodeType(TSubclassOf<UGenericGraphNode> RuntimeNodeType) const override;
};
