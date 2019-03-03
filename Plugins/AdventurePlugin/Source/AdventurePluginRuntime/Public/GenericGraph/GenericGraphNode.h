/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available 
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#pragma once

#include "CoreMinimal.h"
#include "SubclassOf.h"
#include "TextProperty.h"
#include "Map.h"
#include "GenericGraphNode.generated.h"

class UGenericGraph;

/**
* A single node in a generic graph UGenericGraph.
* In Adventure Plugin this serves as a base class for the different nodes in the UQuestGraph and UDialogGraph.
* @see UQuestGraphNode
* @see UDialogGraphNode
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UGenericGraphNode : public UObject
{
	GENERATED_BODY()

public:
	UGenericGraphNode();
	virtual ~UGenericGraphNode();

	/**
	* The graph this node belongs to.
	*/
	UPROPERTY(VisibleDefaultsOnly, Category = "GenericGraphNode")
	UGenericGraph* Graph;

	/**
	* The parent nodes of this node, i.e. from where to the incoming edges come from.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "GenericGraphNode")
	TArray<UGenericGraphNode*> ParentNodes;

	/**
	* The children nodes of this node, i.e. where do the outgoing edges point to.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "GenericGraphNode")
	TArray<UGenericGraphNode*> ChildrenNodes;

	/**
	* A unique ID of this node to identify it unambigously.
	*/
	UPROPERTY()
	FGuid NodeGuid;

	/**
	* Checks whether this is a leaf node, i.e. has no descendants.
	* @return True if this is a leaf node, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Graph")
	bool IsLeafNode() const;

	/**
	* Retrieves the graph this node belongs to.
	* @return The graph this node belongs to, or null if this node is not in a graph.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Graph")
	UGenericGraph* GetGraph() const;

	/**
	* Retrieves the human readable description of this graph node.
	* @return The description of this graph node.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Graph")
	FText GetDescription() const;

	/**
	* Retrieves the human readable description of this graph node.
	* @return The description of this graph node.
	*/
	virtual FText GetDescription_Implementation() const;

	/**
	* Some nodes store some additional data concerning their children. This method clears them.
	* For example, a branching node stores information about which child node should be followed
	* when the condition is true and which to follow when the condition is false.
	*/
	virtual void ResetSpecialChildren() { }

	//////////////////////////////////////////////////////////////////////////
#if WITH_EDITORONLY_DATA

	/**
	* Editor time only. Title of this node to be displayed in the graph.
	* Might be ignored if GetNodeTitle() is overriden.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	FText NodeTitle;

	/**
	* Editor time only. The type of graph inside which this node can be inserted.
	*/
	UPROPERTY(VisibleDefaultsOnly, Category = "GenericGraphNode_Editor")
	TSubclassOf<UGenericGraph> CompatibleGraphType;

	/**
	* Editor time only. The background color of this node when displayed in the graph.
	* Might be ignored if GetBackgroundColor() is overriden.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	FLinearColor BackgroundColor;

	/**
	* Editor time only.
	* When adding a node by right clicking in the graph, this is a name that represents this node in the menu.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	FText ContextMenuName;

	/**
	* Editor time only.
	* When adding a node by right clicking in the graph, this is the category this node belongs to.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	FText ContextMenuCategory;

#endif

#if WITH_EDITOR
	/**
	* Editor time only. Retrieves the background color of this node.
	* @return The background color of this node to be used in the graph.
	*/
	virtual FLinearColor GetBackgroundColor() const;

	/**
	* Editor time only. Retrieves the title of this node.
	* @return The title of this node to be used in the graph.
	*/
	virtual FText GetNodeTitle() const;

	/**
	* Editor time only. Called when the user changes the title of a node in the graph.
	* @param NewTitle The new title of the node.
	*/
	virtual void SetNodeTitle(const FText& NewTitle);

	/**
	* Editor time only.
	* Checks whether it is possible to create a connection between this node and a target node.
	* @param Other The node with which this node might be connected.
	* @param ErrorMessage Output parameter. If the connection cannot be made, this will contain the human readable reason why.
	* @return True if a connection can be made, otherwise false.
	*/
	virtual bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage);

	/**
	* Editor time only.
	* Checks whether the user can add this node to the graph. If false, this node can be only added from code.
	* @return True if the user can add this node to a graph.
	*/
	virtual bool CanAdd() const;

	/**
	* Editor time only.
	* Checks whether the user can delete this node from a graph. If false, this node can be only removed from code.
	* @return True if the user can remvoe this node from a graph.
	*/
	virtual bool CanDelete() const;

	/**
	* Editor time only.
	* Checks whether the user can make a duplicate of this node.
	* @return True if the user can make a duplicate of this node.
	*/
	virtual bool CanDuplicate() const;

	/**
	* Editor time only.
	* Checks whether the user can change the title of this node.
	* @return True if the user can change the title of this node.
	*/
	virtual bool CanRename() const;

#endif
};
