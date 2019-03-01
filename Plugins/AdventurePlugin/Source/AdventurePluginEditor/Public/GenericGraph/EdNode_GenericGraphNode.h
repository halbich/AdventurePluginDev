/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "GenericGraph/GenericGraphNode.h"
#include "EdNode_GenericGraphNode.generated.h"

class UEdGraph_GenericGraph;
class SEdNode_GenericGraphNode;

/**
* Class representing generic node behavior in editor (its pins, copying/deleting etc.)
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UEdNode_GenericGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UEdNode_GenericGraphNode();
	virtual ~UEdNode_GenericGraphNode();

	/**
	* Underlying GenericGraphNode of this editor node
	*/
	UPROPERTY(VisibleAnywhere, Instanced, Category = "GenericGraph")
	UGenericGraphNode* GenericGraphNode;

	/**
	* Slate widget representing this node in graph editor
	*/
	SEdNode_GenericGraphNode* SEdNode;

	/**
	* This method is called when the graph is rebuilding, for every output pin and
	* the node connected to it. It is meant to set the child node to specially
	* reserved property on the parent node, based on the output pin name, when needed.
	* @param Pin Output pin of this node with valid child node connected
	* @param Child Child node connected to this output pin
	*/
	virtual void AddSpecialChild(const UEdGraphPin* Pin, UGenericGraphNode* Child) { }

	/**
	* Allocates default pins for a given node, one input and one output. Should be
	* overriden when the node should have different pin configuration.
	*/
	virtual void AllocateDefaultPins() override;

	/** 
	* Gets the name of this node, shown in title bar. It is extracted from the
	* underlying UGenericGraphNode if present, otherwise default value is used.
	* @return Node title
	*/
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	/**
	* Perform any steps necessary prior to copying a node into the paste buffer
	*/
	virtual void PrepareForCopying() override;

	/**
	* Autowire a newly created node.
	* @param	FromPin	The source pin that caused the new node to be created (typically a drag-release context menu creation).
	*/
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;

	/**
	* Returns background color for this node. It is extracted from the underlying
	* UGenericGraphNode if present, otherwise black.
	* @return Background color
	*/
	virtual FLinearColor GetBackgroundColor() const;

	/*
	* Returns the first input pin of this node
	* @return Input pin
	*/
	virtual UEdGraphPin* GetInputPin() const;

	/*
	* Returns the first output pin of this node
	* @return Output pin
	*/
	virtual UEdGraphPin* GetOutputPin() const;

#if WITH_EDITOR

	/** 
	* Called after applying a transaction to the object.
	* Default implementation simply calls PostEditChange.
	*/
	virtual void PostEditUndo() override;

	/**
	* Whether or not this node can be deleted by user action. Value is extracted from the
	* underlying UGenericGraphNode if present, otherwise true.
	*/
	virtual bool CanUserDeleteNode() const override;

	/** 
	* Whether or not this node can be safely duplicated (via copy/paste, etc...) in the graph.
	* Value is extracted from the underlying UGenericGraphNode if present, otherwise true.
	*/
	virtual bool CanDuplicateNode() const override;
#endif

};
