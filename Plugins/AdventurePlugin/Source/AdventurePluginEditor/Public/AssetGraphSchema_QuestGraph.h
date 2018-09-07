#pragma once

#include "CoreMinimal.h"
#include "GenericGraphEditor/Private/GenericGraphEditorPCH.h"
#include "GenericGraphEditor/Private/GenericGraphAssetEditor/AssetGraphSchema_GenericGraph.h"
#include "AssetGraphSchema_QuestGraph.generated.h"

UCLASS()
class ADVENTUREPLUGINEDITOR_API UAssetGraphSchema_QuestGraph : public UAssetGraphSchema_GenericGraph
{
	GENERATED_BODY()
public:
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
};
