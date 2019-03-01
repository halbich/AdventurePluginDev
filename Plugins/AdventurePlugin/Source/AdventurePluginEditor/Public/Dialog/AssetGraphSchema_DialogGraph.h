#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/AssetGraphSchema_GenericGraph.h"
#include "Dialog/Graph/DialogGraphNode.h"
#include "EdDialogNode.h"
#include "AssetGraphSchema_DialogGraph.generated.h"

class UAdventureCharacter;

/**
* Graph schema for UDialogGraph graph
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UAssetGraphSchema_DialogGraph : public UAssetGraphSchema_GenericGraph
{
	GENERATED_BODY()

public:

	UAssetGraphSchema_DialogGraph();

	/**
	* Determine if a connection can be created between two pins. This overriden method also breaks all other
	* connections from the pin when creating a new one.
	* @param	A	The first pin.
	* @param	B	The second pin.
	* @return	FPinConnectionResponse describing whether the connection is legal and if not, why the connection would fail.
	*/
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

	/**
	* Populates new graph with any default nodes. In this case, adds Main Entry Point node
	* and also automatically sets the player character if unambiguous.
	* @param	Graph	Graph to add the default nodes to
	*/
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;

	virtual TSubclassOf<UEdNode_GenericGraphNode> GetEditorNodeType(TSubclassOf<UGenericGraphNode> RuntimeNodeType) const override;

protected:

	/**
	* When in UE Editor, returns UAdventureCharacter object, which represents given
	* UAdventureCharacterBlueprint asset. Otherwise, returns nullptr.
	* @param AssetData Asset of type UAdventureCharacterBlueprint
	* @return UAdventureCharacter representing given asset
	*/
	UAdventureCharacter* GetCharacterFromAsset(FAssetData& AssetData) const;

	/**
	* Iterates through all UAdventureCharacterBlueprint assets and returns the only one
	* which could be Player character (bIsPlayerCharacter is true). If there is
	* none or more of them, returns nullptr. It is useful for automatic setting
	* of this character in newly created Dialog graph.
	* @return Only Player character candidate or nullptr
	*/
	UAdventureCharacter* GetOnlyPlayerCharacter() const;
};
