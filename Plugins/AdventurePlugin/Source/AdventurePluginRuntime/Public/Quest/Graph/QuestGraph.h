#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraph.h"
#include "Quest/Structs/BoolVariable.h"
#include "Quest/Structs/IntegerVariable.h"
#include "Quest/Structs/StringVariable.h"
#include "QuestGraph.generated.h"

class UQuestGraphNode;
class UAdventurePluginGameContext;

/*
* Delegate for handlers for quest events.
*/
class FQuestEvent;
DECLARE_DYNAMIC_DELEGATE(FQuestEvent);

/**
* This class represents a single quest, things a player has to fulfill to progress through the game.
* It is a data storage for all the variables and flags tracking the state of the quest.
* The UQuestNode nodes in the graph represent the concrete actions the player has to take to complete the quests.
* These nodes can be true or false. Once they are true, they should never be switched back to false.
* That is because these nodes also store dependencies between the actions. Edge between two nodes means that the player must do that action before another one.
* If at any time a node is true but its predecessor is false, it is a bug.
* <p>
* The quest is considered to be completed when a specific node, UQuestGraphNode_End, has all of its predecessors true.
* If the graph was designed and the flags were set correctly, it means that the player took all actions leading up to that end node, so he finished the quest.
* For variables with more complex behavior the designer can define string, integer and boolean variables on a quest.
* The designer can set default values for these variables. The variables are also automatically serialized.
* <p>
* Designer can also define events on the quest. Another blueprint can then subscribe to that event with some method that will be executed when the event is fired.
* These events are the main way how dialogs can affect the game scene. A dialog exists indpendently of the game scene.
* So if a designer wanted a dialog to, for example, start a scripted fight scene, the designer would create an event on a quest called StartFightScene.
* The level blueprint would then bind a handler to that event that would start that fight scene. And dialog would trigger that event when necessary.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UQuestGraph : public UGenericGraph
{
	GENERATED_BODY()

public:
	UQuestGraph();
	virtual ~UQuestGraph();

	/**
	* The last node in the quest graph. When it's true, the quest is complete.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "QuestGraph")
	UQuestGraphNode* EndNode;

	/**
	* Retrieves the state of a quest flag defined on this quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param FlagName The name of the flag whose value is requested.
	* @return True if the flag is set, otherwise false.
	*/
	UFUNCTION(Category = "Adventure Plugin|Quest")
	bool GetFlag(UAdventurePluginGameContext* GameContext, FName FlagName);

	/**
	* Sets a quest flag defined on this quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param FlagName The name of the flag that should be set.
	*/
	UFUNCTION(Category = "Adventure Plugin|Quest")
	void SetFlag(UAdventurePluginGameContext* GameContext, FName FlagName);

	/**
	* Retrieves the value of a boolean variable defined on this quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param VariableName The name of the variable whose value is requested.
	* @return The value of the variable, or false if the variable does not exist in the graph.
	*/
	UFUNCTION(Category = "Adventure Plugin|Quest")
	bool GetBool(UAdventurePluginGameContext* GameContext, FName VariableName);

	/**
	* Changes the value of a boolean variable defined on this quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param VariableName The name of the variable whose value is requested.
	* @param bValue The new value of the variable.
	*/
	UFUNCTION(Category = "Adventure Plugin|Quest")
	bool SetBool(UAdventurePluginGameContext* GameContext, FName VariableName, bool bValue);

	/**
	* Retrieves the value of an integer variable defined on this quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param VariableName The name of the variable whose value is requested.
	* @return The value of the variable, or 0 if the variable does not exist in the graph.
	*/
	UFUNCTION(Category = "Adventure Plugin|Quest")
	int32 GetInteger(UAdventurePluginGameContext* GameContext, FName VariableName);

	/**
	* Changes the value of an integer variable defined on this quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param VariableName The name of the variable whose value is requested.
	* @param Value The new value of the variable.
	*/
	UFUNCTION(Category = "Adventure Plugin|Quest")
	bool SetInteger(UAdventurePluginGameContext* GameContext, FName VariableName, int32 Value);

	/**
	* Retrieves the value of a string variable defined on this quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param VariableName The name of the variable whose value is requested.
	* @return The value of the variable, or an empty string if the variable does not exist in the graph.
	*/
	UFUNCTION(Category = "Adventure Plugin|Quest")
	FString GetString(UAdventurePluginGameContext* GameContext, FName VariableName);

	/**
	* Changes the value of a string variable defined on this quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param VariableName The name of the variable whose value is requested.
	* @param Value The new value of the variable.
	*/
	UFUNCTION(Category = "Adventure Plugin|Quest")
	bool SetString(UAdventurePluginGameContext* GameContext, FName VariableName, FString Value);
	
	/**
	* Retrieves the list of all nodes that can be set to true, i.e. they are not true and all of their predecessors are true.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The list of true nodes.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Quest", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	TArray<UQuestGraphNode*> GetFullfilableNodes(UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext);

	/**
	* Returns true if this graph is complete.
	* Default implementation checks if the (always unique) UQuestGraph#EndNode is true.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if the quest is complete, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Quest", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	virtual bool IsComplete(UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext);

	/**
	* The list of all boolean variables defined on this quest.
	*/
	UPROPERTY(EditAnywhere, Category = "QuestGraph")
	TMap<FName, FBoolVariable> BoolVariables;

	/**
	* The list of all integer variables defined on this quest.
	*/
	UPROPERTY(EditAnywhere, Category = "QuestGraph")
	TMap<FName, FIntegerVariable> IntegerVariables;

	/**
	* The list of all string variables defined on this quest.
	*/
	UPROPERTY(EditAnywhere, Category = "QuestGraph")
	TMap<FName, FStringVariable> StringVariables;

	/**
	* The list of all quest events defined on this quest.
	*/
	UPROPERTY(EditAnywhere, Category = "QuestGraph")
	TMap<FName, FQuestEvent> QuestEvents;

protected:

	/**
	* Converts the graph name to FText and return it. Used often when logging errors.
	* @return The name of the graph as FText.
	*/
	FText GetGraphNameText();

	/**
	* For the passes variable, get a new name that includes the name of the graph, so the name is unique across all graphs.
	* @param VariableName The variable for which we need the qualified name.
	* @return The qualified name of this variable.
	*/
	FName GetQualifiedVariableName(FName VariableName);
};
