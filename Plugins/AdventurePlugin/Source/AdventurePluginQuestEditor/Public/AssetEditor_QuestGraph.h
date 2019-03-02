#pragma once

#include "CoreMinimal.h"
#include "GraphEditor.h"
#include "GenericGraph/AssetEditor_GenericGraph.h"

class UQuestGraphNode;

/**
* Editor class for editing assets of type UQuestGraph.
*/
class FAssetEditor_QuestGraph : public FAssetEditor_GenericGraph
{
protected:

	virtual FGraphAppearanceInfo GetViewportWidgetAppearanceInfo() const override;

	/**
	* Returns graph schema class for this graph, derived from UEdGraphSchema.
	* @return UAssetGraphSchema_QuestGraph class
	*/
	virtual UClass* GetGraphSchemaClass() const override;

	/**
	* Executes basic rebuild of the graph, then finds the UQuestGraphNode_End
	* end node in the graph and stores it.
	*/
	virtual void RebuildGenericGraph() override;
};