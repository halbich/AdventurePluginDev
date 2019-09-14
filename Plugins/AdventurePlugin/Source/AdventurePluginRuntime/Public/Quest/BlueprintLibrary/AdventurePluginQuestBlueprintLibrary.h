#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Quest/Structs/QuestGraphBool.h"
#include "Quest/Structs/QuestGraphFlag.h"
#include "Quest/Structs/QuestGraphEvent.h"
#include "Quest/Structs/QuestGraphInteger.h"
#include "Quest/Structs/QuestGraphString.h"
#include "AdventurePluginQuestBlueprintLibrary.generated.h"

/**
* This library defines static functions regarding quests and exposes them to blueprints.
*/
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginQuestBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	* Retrieves the value of a boolean variable stored on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestBoolVariable Identification of the variable whose value is requested.
	* @return The variable's value, or false if the identification of variable or game context is invalid.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Quest")
	static bool GetQuestBool(UAdventurePluginGameContext* GameContext, FQuestGraphBool QuestBoolVariable);

	/**
	* Changes the value of a boolean variable stored on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestBoolVariable Identification of the variable whose value should be changed.
	* @param bNewValue The new value of the quest variable.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest")
	static void SetQuestBool(UAdventurePluginGameContext* GameContext, FQuestGraphBool QuestBoolVariable, bool bNewValue);

	/**
	* Retrieves the state of a flag set on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestFlag Identification of the flag whose value is requested.
	* @return True if the flag is set, false if not set or if the game context or flag identification is invalid.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Quest")
	static bool GetQuestFlag(UAdventurePluginGameContext* GameContext, FQuestGraphFlag QuestFlag);

	/**
	* Sets a flag defined on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestFlag Identification of the flag that should be set.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest")
	static void SetQuestFlag(UAdventurePluginGameContext* GameContext, FQuestGraphFlag QuestFlag);

	/**
	* Retrieves the value of an integer variable stored on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestIntegerVariable Identification of the variable whose value is requested.
	* @return The variable's value, or 0 if the identification of variable or game context is invalid.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Quest")
	static int32 GetQuestInteger(UAdventurePluginGameContext* GameContext, FQuestGraphInteger QuestIntegerVariable);

	/**
	* Changes the value of an integer variable stored on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestIntegerVariable Identification of the variable whose value should be changed.
	* @param NewValue The new value of the quest variable.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest")
	static void SetQuestInteger(UAdventurePluginGameContext* GameContext, FQuestGraphInteger QuestIntegerVariable, int32 NewValue);

	/**
	* Retrieves the value of a string variable stored on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestStringVariable Identification of the variable whose value is requested.
	* @return The variable's value, or empty string if the identification of variable or game context is invalid.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Quest")
	static FString GetQuestString(UAdventurePluginGameContext* GameContext, FQuestGraphString QuestStringVariable);

	/**
	* Changes the value of a string variable stored on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestStringVariable Identification of the variable whose value should be changed.
	* @param NewValue The new value of the quest variable.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest")
	static void SetQuestString(UAdventurePluginGameContext* GameContext, FQuestGraphString QuestStringVariable, const FString& NewValue);

	/**
	* Binds a handler for a quest event. When that event is fired, the passed method will be executed.
	* Note - there can be only one handler bound to an event. When you call BindQuestEvent() again for the same event, the old handler will be discarded.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestEvent The identification of the quest event the handler should handle.
	* @param QuestEventHandler The method to be called when the event is fired.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest")
	static bool BindQuestEvent(UAdventurePluginGameContext* GameContext, FQuestGraphEvent QuestEvent, FQuestEvent QuestEventHandler);

	/**
	* Triggers an event, which executes method previously bound to this event.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestEvent The identification of the quest event to trigger.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest")
	static void FireQuestEvent(UAdventurePluginGameContext* GameContext, FQuestGraphEvent QuestEvent);
};
