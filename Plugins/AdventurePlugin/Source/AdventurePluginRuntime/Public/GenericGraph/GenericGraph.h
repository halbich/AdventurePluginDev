/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#pragma once

#include "CoreMinimal.h"
#include "GenericGraphNode.h"
#include "GameplayTagContainer.h"
#include "GenericGraph.generated.h"

#define LOG_INFO(FMT, ...) UE_LOG(GenericGraphRuntime, Display, (FMT), ##__VA_ARGS__)
/**
* This class represents a generic graph with no inherent functionality.
* In Adventure Plugin it servers as a base class for Dialog Graph and Quest Graph.
* @see UDialogGraph
* @see UQuestGraph
* This is the runtime version of the graph that contains only data needed to read graph data at runtime.
* For editing in editor, @see UEdGraph
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UGenericGraph : public UObject
{
	GENERATED_BODY()

public:
	UGenericGraph();
	virtual ~UGenericGraph();
	/**
	* The user friendly name of this graph.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraph")
	FString Name;
	/*
	* The type of nodes that can be contained in this graph.
	*/
	UPROPERTY()
	TSubclassOf<UGenericGraphNode> NodeType;
	/*
	* The tags defined for this graph.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GenericGraph")
	FGameplayTagContainer GraphTags;
	/**
	* All the root nodes of this graph, i.e. nodes that have no incoming edges.
	* By going through their descendats we can traverse all nodes in the graph.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "GenericGraph")
	TArray<UGenericGraphNode*> RootNodes;
	/**
	* All nodes in this graph.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "GenericGraph")
	TArray<UGenericGraphNode*> AllNodes;
	/**
	* Removes all nodes and edges from this graph.
	*/
	void ClearGraph();

#if WITH_EDITORONLY_DATA
	/**
	* Ëditor time only. The editor time version of this graph.
	* Needed for actual editation of the graph in the editor.
	*/
	UPROPERTY()
	class UEdGraph* EdGraph;
	/**
	* Ëditor time only. If true, it should be possible to rename nodes in the graph.
	*/
	UPROPERTY()
	bool bCanRenameNode;
#endif
};
