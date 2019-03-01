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

/**
* Action to add a node to the graph 
*/
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

/**
* Graph schema for UGenericGraph graph, used as a base for UDialogGraph schema and UQuestGraph schema
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UAssetGraphSchema_GenericGraph : public UEdGraphSchema
{
	GENERATED_BODY()

public:

	/**
	* Adds actions for breaking the links between two nodes to the context menu.
	*/
	void GetBreakLinkToSubMenuActions(class FMenuBuilder& MenuBuilder, class UEdGraphPin* InGraphPin);

	/**
	* @return The type of graph (function vs. ubergraph) that this that TestEdGraph is. 
	*/
	virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override;

	/**
	* Get all actions that can be performed when right clicking on a graph or drag-releasing on a graph from a pin.
	* @param [in,out]	ContextMenuBuilder	The context (graph, dragged pin, etc...) and output menu builder.
	*/
 	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

	/**
	* Gets actions that should be added to the right-click context menu for a node or pin
	* @param	CurrentGraph	The current graph.
	* @param	InGraphNode		The node to get the context menu for, if any.
	* @param	InGraphPin		The pin clicked on, if any, to provide additional context
	* @param	MenuBuilder		The menu builder to append actions to.
	* @param	bIsDebugging	Is the graph editor currently part of a debugging session (any non-debugging commands should be disabled)
	*/
 	virtual void GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, class FMenuBuilder* MenuBuilder, bool bIsDebugging) const override;

	/**
	* Determine if a connection can be created between two pins.
	* @param	A	The first pin.
	* @param	B	The second pin.
	* @return	FPinConnectionResponse describing whether the connection is legal and if not, why the connection would fail.
	*/
 	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

	/**
	* Returns new FConnectionDrawingPolicy from this schema.
	*/
	virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;

	/**
	* Gets the draw color of a pin based on it's type.
	* @param	PinType	The type to convert into a color.
	* @return	The color representing the passed in type.
	*/
 	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;

 	virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;

	/**
	* Breaks all links from/to a single pin
	* @param	TargetPin	The pin to break links on
	* @param	bSendsNodeNotifcation	Whether to send a notification to the node post pin connection change
	*/
 	virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;

	/**
	* Breaks the link between two nodes.
	* @param	SourcePin	The pin where the link begins.
	* @param	TargetLink	The pin where the link ends.
	*/
	virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;

	/*
	* Some schemas have nodes that support the user dynamically adding pins when dropping a connection on the node
	* @param InTargetNode			Node to check for pin adding support
	* @param InSourcePinName		Name of the pin being dropped, a new pin of similar name will be constructed
	* @param InSourcePinType		Type of pin to drop onto the node
	* @param InSourcePinDirection	Direction of the source pin
	* @return						Returns the new pin if created
	*/
	virtual UEdGraphPin* DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const override;

	/**
	* Checks if the node supports dropping a pin on it
	* @param InTargetNode			Node to check for pin adding support
	* @param InSourcePinType		Type of pin to drop onto the node
	* @param InSourcePinDirection	Direction of the source pin
	* @param OutErrorMessage		Only filled with an error if there is pin add support but there is an error with the pin type
	* @return						Returns TRUE if there is support for dropping the pin on the node
	*/
	virtual bool SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const override;

	/**
	* Checks if a CacheRefreshID is out of date
	* @param InVisualizationCacheID	The current refresh ID to check if out of date
	* @return						TRUE if dirty
	*/
	virtual bool IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const override;

	/** 
	* Returns the current cache title refresh ID that is appropriate for the passed node
	*/
	virtual int32 GetCurrentVisualizationCacheID() const override;

	/** 
	* Forces cached visualization data to refresh
	*/
	virtual void ForceVisualizationCacheClear() const override;

private:

	static int32 CurrentCacheRefreshID;

protected:

	/**
	* Returns editor node type which should be used for visualization of the given runtime node type
	* in this graph.
	* @param RuntimeNodeType Runtime node type for which corresponding editor node type should be returned
	* @return Editor node type
	*/
	virtual TSubclassOf<UEdNode_GenericGraphNode> GetEditorNodeType(TSubclassOf<UGenericGraphNode> RuntimeNodeType) const;
};

