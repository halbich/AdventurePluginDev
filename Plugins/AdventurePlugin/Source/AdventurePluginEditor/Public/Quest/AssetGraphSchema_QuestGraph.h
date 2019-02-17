#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/AssetGraphSchema_GenericGraph.h"
#include "Quest/Graph/QuestGraphNode.h"
#include "EdQuestNode.h"
#include "AssetGraphSchema_QuestGraph.generated.h"
UCLASS()
class ADVENTUREPLUGINEDITOR_API UAssetGraphSchema_QuestGraph : public UAssetGraphSchema_GenericGraph
{
	GENERATED_BODY()

public:

	UAssetGraphSchema_QuestGraph();
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	virtual TSubclassOf<UEdNode_GenericGraphNode> GetEditorNodeType(TSubclassOf<UGenericGraphNode> RuntimeNodeType) const override;

protected:

	UPROPERTY()
		TMap<TSubclassOf<UQuestGraphNode>, TSubclassOf<UEdQuestNode>> EditorNodeMap;
};
