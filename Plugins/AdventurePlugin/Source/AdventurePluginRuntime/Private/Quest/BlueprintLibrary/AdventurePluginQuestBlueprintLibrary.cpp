#include "BlueprintLibrary/AdventurePluginQuestBlueprintLibrary.h"
#include "AdventurePluginRuntime.h"
#include "AdventurePluginGameContext.h"

bool UAdventurePluginQuestBlueprintLibrary::GetQuestBool(UAdventurePluginGameContext* GameContext, FQuestGraphBool QuestBoolVariable)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("GetQuestBool")))
	{
		return false;
	}
	if (!IsValid(QuestBoolVariable.Quest))
	{
		LOG_Warning(NSLOCTEXT("AP", "GetQuestBool_QuestNull", "GetQuestBool:Quest is null or invalid"));
		return false;
	}
	return QuestBoolVariable.Quest->GetBool(GameContext, QuestBoolVariable.BoolName);
}
void UAdventurePluginQuestBlueprintLibrary::SetQuestBool(UAdventurePluginGameContext* GameContext, FQuestGraphBool QuestBoolVariable, bool bNewValue)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("SetQuestBool")))
	{
		return;
	}
	if (!IsValid(QuestBoolVariable.Quest))
	{
		LOG_Warning(NSLOCTEXT("AP", "SetQuestBool_QuestNull", "SetQuestBool:Quest is null or invalid"));
		return;
	}
	QuestBoolVariable.Quest->SetBool(GameContext, QuestBoolVariable.BoolName, bNewValue);
}

bool UAdventurePluginQuestBlueprintLibrary::GetQuestFlag(UAdventurePluginGameContext* GameContext, FQuestGraphFlag QuestFlag)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("GetQuestFlag")))
	{
		return false;
	}
	if (!IsValid(QuestFlag.Quest))
	{
		LOG_Warning(NSLOCTEXT("AP", "GetQuestFlag_QuestNull", "GetQuestFlag:Quest is null or invalid"));
		return false;
	}
	return QuestFlag.Quest->GetFlag(GameContext, QuestFlag.FlagName);
}
void UAdventurePluginQuestBlueprintLibrary::SetQuestFlag(UAdventurePluginGameContext* GameContext, FQuestGraphFlag QuestFlag)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("SetQuestFlag")))
	{
		return;
	}
	if (!IsValid(QuestFlag.Quest))
	{
		LOG_Warning(NSLOCTEXT("AP", "SetQuestFlag_QuestNull", "SetQuestFlag:Quest is null or invalid"));
		return;
	}
	QuestFlag.Quest->SetFlag(GameContext, QuestFlag.FlagName);
}

int32 UAdventurePluginQuestBlueprintLibrary::GetQuestInteger(UAdventurePluginGameContext* GameContext, FQuestGraphInteger QuestIntegerVariable)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("GetQuestInteger")))
	{
		return 0;
	}
	if (!IsValid(QuestIntegerVariable.Quest))
	{
		LOG_Warning(NSLOCTEXT("AP", "GetQuestInteger_QuestNull", "GetQuestInteger:Quest is null or invalid"));
		return 0;
	}
	return QuestIntegerVariable.Quest->GetInteger(GameContext, QuestIntegerVariable.IntegerName);
}
void UAdventurePluginQuestBlueprintLibrary::SetQuestInteger(UAdventurePluginGameContext* GameContext, FQuestGraphInteger QuestIntegerVariable, int32 NewValue)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("SetQuestInteger")))
	{
		return;
	}
	if (!IsValid(QuestIntegerVariable.Quest))
	{
		LOG_Warning(NSLOCTEXT("AP", "SetQuestInteger_QuestNull", "SetQuestInteger:Quest is null or invalid"));
		return;
	}
	QuestIntegerVariable.Quest->SetInteger(GameContext, QuestIntegerVariable.IntegerName, NewValue);
}

FString UAdventurePluginQuestBlueprintLibrary::GetQuestString(UAdventurePluginGameContext* GameContext, FQuestGraphString QuestStringVariable)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("GetQuestString")))
	{
		return FString();
	}
	if (!IsValid(QuestStringVariable.Quest))
	{
		LOG_Warning(NSLOCTEXT("AP", "GetQuestString_QuestNull", "GetQuestString:Quest is null or invalid"));
		return FString();
	}
	return QuestStringVariable.Quest->GetString(GameContext, QuestStringVariable.StringName);
}
void UAdventurePluginQuestBlueprintLibrary::SetQuestString(UAdventurePluginGameContext* GameContext, FQuestGraphString QuestStringVariable, const FString& NewValue)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("SetQuestString")))
	{
		return;
	}
	if (!IsValid(QuestStringVariable.Quest))
	{
		LOG_Warning(NSLOCTEXT("AP", "SetQuestString_QuestNull", "SetQuestString:Quest is null or invalid"));
		return;
	}
	QuestStringVariable.Quest->SetString(GameContext, QuestStringVariable.StringName, NewValue);
}

bool UAdventurePluginQuestBlueprintLibrary::BindQuestEvent(UAdventurePluginGameContext* GameContext, FQuestGraphEvent QuestEvent, FQuestEvent QuestEventHandler)
{
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("BindQuestEvent")))
	{
		return false;
	}

	if (!IsValid(QuestEvent.Quest))
	{
		LOG_Warning(NSLOCTEXT("AP", "QuestGraphInvalid", "Bind event::graph is invalid"));
		return false;
	}

	TMap<FName, FQuestEvent>& QuestEventsMap = QuestEvent.Quest->QuestEvents;
	if (!QuestEventsMap.Contains(QuestEvent.EventName))
	{
		LOG_Warning(NSLOCTEXT("AP", "EventNameUndefined", "Bind event::event name is not defined in quest"));
		return false;
	}

	QuestEventsMap.Add(QuestEvent.EventName, QuestEventHandler);
	return true;
}