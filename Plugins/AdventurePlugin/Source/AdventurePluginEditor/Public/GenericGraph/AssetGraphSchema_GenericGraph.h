/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraph.h"
#include "GenericGraph/GenericGraphNode.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "EdGraph/EdGraphSchema.h"
#include "AssetGraphSchema_GenericGraph.generated.h"

class UEdNode_GenericGraphNode;

/** Action to add a node to the graph */
USTRUCT()
struct ADVENTUREPLUGINEDITOR_API FAssetSchemaAction_GenericGraph_NewNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

public:
	FAssetSchemaAction_GenericGraph_NewNode(): NodeTemplate(nullptr) {}

	FAssetSchemaAction_GenericGraph_NewNode(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), NodeTemplate(nullptr) {}

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	UEdNode_GenericGraphNode* NodeTemplate;
};

UCLASS()
class ADVENTUREPLUGINEDITOR_API UAssetGraphSchema_GenericGraph : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	void GetBreakLinkToSubMenuActions(class FMenuBuilder& MenuBuilder, class UEdGraphPin* InGraphPin);

	virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override;

 	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

 	virtual void GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, class FMenuBuilder* MenuBuilder, bool bIsDebugging) const override;

 	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

	virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;

 	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;

 	virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;

 	virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;

	virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;

	virtual UEdGraphPin* DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const override;

	virtual bool SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const override;

	virtual bool IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const override;

	virtual int32 GetCurrentVisualizationCacheID() const override;

	virtual void ForceVisualizationCacheClear() const override;

private:
	static int32 CurrentCacheRefreshID;

protected:
	UPROPERTY()
		TMap<TSubclassOf<UGenericGraphNode>, TSubclassOf<UEdNode_GenericGraphNode>> EditorNodeMap;

	virtual TSubclassOf<UEdNode_GenericGraphNode> GetEditorNodeType(TSubclassOf<UGenericGraphNode> RuntimeNodeType) const;

	const TSubclassOf<UEdNode_GenericGraphNode>* FindEditorNodeForRuntimeNode(TSubclassOf<UGenericGraphNode> RuntimeNodeType) const;
};

