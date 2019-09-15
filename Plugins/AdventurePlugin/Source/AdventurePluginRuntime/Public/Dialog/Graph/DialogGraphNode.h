#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraph.h"
#include "GenericGraph/GenericGraphNode.h"
#include "Dialog/Structs/DialogLineData.h"
#include "AdventurePluginRuntime.h"
#include "DialogGraphNode.generated.h"

class UDialogController;
class UAdventurePluginGameContext;
class UDialogGraph;

/**
* The base class for all nodes that can be added into the dialog graph. @see UDialogGraph.
*/
UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode : public UGenericGraphNode
{
	GENERATED_BODY()

public:
	UDialogGraphNode();
	virtual ~UDialogGraphNode();
	virtual FText GetDescription_Implementation() const;

	/**
	* The human readable ID identifying this node. 
	* Used e.g. for GOTO or identifying entry points.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogNode")
	FName Id;

#if WITH_EDITORONLY_DATA

	/**
	* A text that can be displayed in the node.
	* For example, a fire event note might have a short description describing what will happen.
	*/
	UPROPERTY(EditAnywhere, Category = "DialogNode")
	FText Note;

#endif

#if WITH_EDITOR
	virtual void SetNodeTitle(const FText& NewTitle) override;
	virtual bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage) override;
	virtual bool CanRename() const override;
#endif

	/**
	* Executes the action this node represents, like changing a variable, displaying a dialog line, firing an event etc.
	* Default implementation does nothing and returns true. Expected to be overriden.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if the executon should continue, false if the execution should be paused, since we are waiting for something.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext)
	{
		return true;
	}

	/**
	* Returns the next node to be executed based on the current state of the game.
	* Default implementation returns the first child if there is any, or null if this node has no children.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The next node to be executed, or null if we are at the end of graph execution
	*/
	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* GameContext)
	{
		return ChildrenNodes.Num() > 0 ? Cast<UDialogGraphNode>(ChildrenNodes[0]) : nullptr;
	}

	/**
	* Returns true if this node is a dialog option and can be presented to the player.
	* Default implementation returns false.
	* @return True if this is a dialog option.
	*/
	virtual bool IsDialogOption() const
	{
		return false;
	}

	/**
	* Returns the dialog line this node represents, or empty Dialog line if this is not a dialog line.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The dialog line this node represents.
	*/
	virtual FDialogLineData GetDialogLine(UAdventurePluginGameContext* GameContext) const
	{
		return FDialogLineData();
	}

	virtual class UWorld* GetWorld() const override {
		return Graph->GetWorld();
	}
	
protected:

	/**
	* Returns the dialog graph this node belongs to.
	* @return The dialog graph this node belongs to.
	*/
	UDialogGraph * GetDialogGraph() const;
};
