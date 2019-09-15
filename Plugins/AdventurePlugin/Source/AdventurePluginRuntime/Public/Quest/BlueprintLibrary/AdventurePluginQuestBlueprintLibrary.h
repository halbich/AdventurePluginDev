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
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Quest", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static bool GetQuestBool(UAdventurePluginGameContext* GameContextOverride, FQuestGraphBool QuestBoolVariable, UObject* WorldObjectContext);

	/**
	* Changes the value of a boolean variable stored on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestBoolVariable Identification of the variable whose value should be changed.
	* @param bNewValue The new value of the quest variable.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static void SetQuestBool(UAdventurePluginGameContext* GameContextOverride, FQuestGraphBool QuestBoolVariable, bool bNewValue, UObject* WorldObjectContext);

	/**
	* Retrieves the state of a flag set on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestFlag Identification of the flag whose value is requested.
	* @return True if the flag is set, false if not set or if the game context or flag identification is invalid.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Quest", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static bool GetQuestFlag(UAdventurePluginGameContext* GameContextOverride, FQuestGraphFlag QuestFlag, UObject* WorldObjectContext);

	/**
	* Sets a flag defined on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestFlag Identification of the flag that should be set.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static void SetQuestFlag(UAdventurePluginGameContext* GameContextOverride, FQuestGraphFlag QuestFlag, UObject* WorldObjectContext);

	/**
	* Retrieves the value of an integer variable stored on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestIntegerVariable Identification of the variable whose value is requested.
	* @return The variable's value, or 0 if the identification of variable or game context is invalid.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Quest", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static int32 GetQuestInteger(UAdventurePluginGameContext* GameContextOverride, FQuestGraphInteger QuestIntegerVariable, UObject* WorldObjectContext);

	/**
	* Changes the value of an integer variable stored on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestIntegerVariable Identification of the variable whose value should be changed.
	* @param NewValue The new value of the quest variable.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static void SetQuestInteger(UAdventurePluginGameContext* GameContextOverride, FQuestGraphInteger QuestIntegerVariable, int32 NewValue, UObject* WorldObjectContext);

	/**
	* Retrieves the value of a string variable stored on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestStringVariable Identification of the variable whose value is requested.
	* @return The variable's value, or empty string if the identification of variable or game context is invalid.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Quest", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static FString GetQuestString(UAdventurePluginGameContext* GameContextOverride, FQuestGraphString QuestStringVariable, UObject* WorldObjectContext);

	/**
	* Changes the value of a string variable stored on a quest.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestStringVariable Identification of the variable whose value should be changed.
	* @param NewValue The new value of the quest variable.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static void SetQuestString(UAdventurePluginGameContext* GameContextOverride, FQuestGraphString QuestStringVariable, const FString& NewValue, UObject* WorldObjectContext);

	/**
	* Binds a handler for a quest event. When that event is fired, the passed method will be executed.
	* Note - there can be only one handler bound to an event. When you call BindQuestEvent() again for the same event, the old handler will be discarded.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestEvent The identification of the quest event the handler should handle.
	* @param QuestEventHandler The method to be called when the event is fired.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static bool BindQuestEvent(UAdventurePluginGameContext* GameContextOverride, FQuestGraphEvent QuestEvent, FQuestEvent QuestEventHandler, UObject* WorldObjectContext);

	/**
	* Triggers an event, which executes method previously bound to this event.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param QuestEvent The identification of the quest event to trigger.
	*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|Quest", meta = (WorldContext = WorldObjectContext, AdvancedDisplay = GameContextOverride))
	static void FireQuestEvent(UAdventurePluginGameContext* GameContextOverride, FQuestGraphEvent QuestEvent, UObject* WorldObjectContext);
};
