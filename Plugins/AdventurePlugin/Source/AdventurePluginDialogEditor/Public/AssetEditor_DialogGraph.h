#pragma once

#include "CoreMinimal.h"
#include "GraphEditor.h"
#include "GenericGraph/AssetEditor_GenericGraph.h"

class UDialogGraphNode;
class UDialogGraph;

/**
* Editor for editing assets of type UDialogGraph
*/
class FAssetEditor_DialogGraph : public FAssetEditor_GenericGraph
{
protected:
	virtual FGraphAppearanceInfo GetViewportWidgetAppearanceInfo() const override;
	virtual UClass* GetGraphSchemaClass() const override;

	/**
	* Executes basic rebuild of the graph, then stores every entry point node
	* and every node with an Id to the corresponding map.
	*/
	virtual void RebuildGenericGraph() override;
private:

	/**
	* Iterates through all nodes in the graph and inserts those
	* which has an Id to the map for quicker access.
	*/
	void FillIdToNodeMap(UDialogGraph* Graph);
};