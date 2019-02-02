#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/AssetGraphSchema_GenericGraph.h"
#include "Dialog/Graph/DialogGraphNode.h"
#include "EdDialogNode.h"
#include "AssetGraphSchema_DialogGraph.generated.h"

class UAdventureCharacter;

UCLASS()
class ADVENTUREPLUGINEDITOR_API UAssetGraphSchema_DialogGraph : public UAssetGraphSchema_GenericGraph
{
	GENERATED_BODY()

public:

	UAssetGraphSchema_DialogGraph();
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	virtual TSubclassOf<UEdNode_GenericGraphNode> GetEditorNodeType(TSubclassOf<UGenericGraphNode> RuntimeNodeType) const override;

protected:

	UPROPERTY()
	TMap<TSubclassOf<UDialogGraphNode>, TSubclassOf<UEdDialogNode>> EditorNodeMap;
	UAdventureCharacter* GetCharacterFromAsset(FAssetData& AssetData) const;
	UAdventureCharacter* GetOnlyPlayerCharacter() const;
};
