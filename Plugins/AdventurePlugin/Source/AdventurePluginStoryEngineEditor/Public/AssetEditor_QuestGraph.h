#pragma once

#include "CoreMinimal.h"
#include "GraphEditor.h"
#include "GenericGraphEditor/Private/GenericGraphAssetEditor/AssetEditor_GenericGraph.h"

class UQuestGraphNode;

class FAssetEditor_QuestGraph : public FAssetEditor_GenericGraph
{
protected:
	virtual FGraphAppearanceInfo GetViewportWidgetAppearanceInfo() const override;
	virtual UClass* GetGraphSchemaClass() const override;
	virtual void RebuildGenericGraph() override;
};