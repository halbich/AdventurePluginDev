#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph_GenericGraph.generated.h"

class UGenericGraph;
class UGenericGraphNode;
class UEdNode_GenericGraphNode;

UCLASS()
class UEdGraph_GenericGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UEdGraph_GenericGraph();
	virtual ~UEdGraph_GenericGraph();

	virtual void RebuildGenericGraph();

	UGenericGraph* GetGenericGraph() const;

	virtual bool Modify(bool bAlwaysMarkDirty = true) override;
	virtual void PostEditUndo() override;

	UPROPERTY(Transient)
	TMap<UGenericGraphNode*, UEdNode_GenericGraphNode*> NodeMap;

protected:

	void Clear();
};
