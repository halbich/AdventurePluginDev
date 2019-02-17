#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraphNode.h"
#include "QuestGraphNode.generated.h"

class UAdventurePluginGameContext;
/**
* Base class for nodes in a quest, usually represents an action a player can take.
* @see UQuestGraph
*/
UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UQuestGraphNode : public UGenericGraphNode
{
	GENERATED_BODY()

public:
	UQuestGraphNode();
	virtual ~UQuestGraphNode();

	/**
	* Checks whether this node is satisfied, i.e. the player took all actions necessary for this node to be true.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if this node is satisfied.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Quest")
	virtual bool IsSatisfied(UAdventurePluginGameContext* GameContext)
	{ 
		return true; 
	}
	/**
	* Checks whether all parent nodes of this node are satisfied.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if all parent nodes of this node are satisfied.
	*/
	bool ParentNodesSatisfied(UAdventurePluginGameContext* GameContext);

#if WITH_EDITORONLY_DATA
	/*TODO: Bind to some nice picker of available locations.*/
	/**
	* The location where the user can do this action.
	* Will be shown in the quest node.
	*/
	UPROPERTY(EditAnywhere, Category = "QuestNode")
	FText Location;

#endif

#if WITH_EDITOR
	virtual bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage) override;

	virtual bool CanRename() const override;

#endif

};
