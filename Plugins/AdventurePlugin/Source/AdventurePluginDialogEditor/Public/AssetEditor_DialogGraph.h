#pragma once

#include "CoreMinimal.h"
#include "GraphEditor.h"
//#include "GenericGraphEditor/Private/AssetTypeActions_GenericGraph.h"
#include "GenericGraphEditor/Private/GenericGraphAssetEditor/AssetEditor_GenericGraph.h"

class FAssetEditor_DialogGraph : public FAssetEditor_GenericGraph
{
protected:
	virtual FGraphAppearanceInfo GetViewportWidgetAppearanceInfo() const override;
	virtual UClass* GetGraphSchemaClass() const override;
};