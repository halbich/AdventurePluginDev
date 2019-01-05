#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/AssetGraphSchema_GenericGraph.h"
#include "EdDialogNode.h"
#include "AssetGraphSchema_DialogGraph.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UAssetGraphSchema_DialogGraph : public UAssetGraphSchema_GenericGraph
{
	GENERATED_BODY()
public:
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	virtual TSubclassOf<UEdNode_GenericGraphNode> GetEditorNodeType() const override;
};
