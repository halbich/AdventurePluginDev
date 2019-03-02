#pragma once

#include "CoreMinimal.h"
#include "GraphEditor.h"
#include "GenericGraph/AssetEditor_GenericGraph.h"

class UDialogGraphNode;
class UDialogGraph;

/**
* Editor class for editing assets of type UDialogGraph.
*/
class FAssetEditor_DialogGraph : public FAssetEditor_GenericGraph
{
protected:

	virtual FGraphAppearanceInfo GetViewportWidgetAppearanceInfo() const override;

	/**
	* Returns graph schema class for this graph, derived from UEdGraphSchema.
	* @return UAssetGraphSchema_DialogGraph class
	*/
	virtual UClass* GetGraphSchemaClass() const override;

	/**
	* Executes basic rebuild of the graph, then stores every entry point node
	* (UDialogGraphNode_EntryMain or UDialogGraphNode_EntrySecondary)
	* and every node with a UDialogGraphNode#Id to the corresponding map.
	*/
	virtual void RebuildGenericGraph() override;

private:

	/**
	* Iterates through all nodes in the graph and inserts those
	* which have a UDialogGraphNode#Id to the map for quicker access.
	*/
	void FillIdToNodeMap(UDialogGraph* Graph);
};