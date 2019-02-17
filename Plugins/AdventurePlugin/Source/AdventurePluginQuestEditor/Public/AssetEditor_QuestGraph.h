#pragma once

#include "CoreMinimal.h"
#include "GraphEditor.h"
#include "GenericGraph/AssetEditor_GenericGraph.h"

class UQuestGraphNode;
/**
* The editor for FQuestGraph data asset.
*/
class FAssetEditor_QuestGraph : public FAssetEditor_GenericGraph
{
protected:
	virtual FGraphAppearanceInfo GetViewportWidgetAppearanceInfo() const override;
	virtual UClass* GetGraphSchemaClass() const override;
	virtual void RebuildGenericGraph() override;
};