#pragma once

#include "CoreMinimal.h"
#include "GraphEditor.h"
#include "GenericGraph/AssetEditor_GenericGraph.h"

class UQuestGraphNode;

/**
* Editor for editing assets of type UQuestGraph
*/
class FAssetEditor_QuestGraph : public FAssetEditor_GenericGraph
{
protected:
	virtual FGraphAppearanceInfo GetViewportWidgetAppearanceInfo() const override;
	virtual UClass* GetGraphSchemaClass() const override;

	/**
	* Executes basic rebuild of the graph, then finds end node in the graph
	* and stores it.
	*/
	virtual void RebuildGenericGraph() override;
};