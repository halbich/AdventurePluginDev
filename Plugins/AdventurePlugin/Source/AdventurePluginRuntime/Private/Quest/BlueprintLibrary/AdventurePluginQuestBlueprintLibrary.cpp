#include "Quest/BlueprintLibrary/AdventurePluginQuestBlueprintLibrary.h"
#include "AdventurePluginRuntime.h"
#include "Common/AdventurePluginGameContext.h"
#include "Quest/Graph/QuestGraph.h"

bool UAdventurePluginQuestBlueprintLibrary::GetQuestBool(UAdventurePluginGameContext* GameContextOverride, FQuestGraphBool QuestBoolVariable, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("GetQuestBool")))
	{
		return false;
	}
	if (!IsValid(QuestBoolVariable.Quest))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestLibrary_GetQuestBool_QuestNull", "GetQuestBool:Quest is null or invalid."));
		return false;
	}
	return QuestBoolVariable.Quest->GetBool(GameContext, QuestBoolVariable.BoolName);
}

void UAdventurePluginQuestBlueprintLibrary::SetQuestBool(UAdventurePluginGameContext* GameContextOverride, FQuestGraphBool QuestBoolVariable, bool bNewValue, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("SetQuestBool")))
	{
		return;
	}
	if (!IsValid(QuestBoolVariable.Quest))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestLibrary_SetQuestBool_QuestNull", "SetQuestBool:Quest is null or invalid."));
		return;
	}
	QuestBoolVariable.Quest->SetBool(GameContext, QuestBoolVariable.BoolName, bNewValue);
}

bool UAdventurePluginQuestBlueprintLibrary::GetQuestFlag(UAdventurePluginGameContext* GameContextOverride, FQuestGraphFlag QuestFlag, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("GetQuestFlag")))
	{
		return false;
	}
	if (!IsValid(QuestFlag.Quest))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestLibrary_GetQuestFlag_QuestNull", "GetQuestFlag:Quest is null or invalid."));
		return false;
	}
	return QuestFlag.Quest->GetFlag(GameContext, QuestFlag.FlagName);
}

void UAdventurePluginQuestBlueprintLibrary::SetQuestFlag(UAdventurePluginGameContext* GameContextOverride, FQuestGraphFlag QuestFlag, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("SetQuestFlag")))
	{
		return;
	}
	if (!IsValid(QuestFlag.Quest))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestLibrary_SetQuestFlag_QuestNull", "SetQuestFlag:Quest is null or invalid."));
		return;
	}
	QuestFlag.Quest->SetFlag(GameContext, QuestFlag.FlagName);
}

int32 UAdventurePluginQuestBlueprintLibrary::GetQuestInteger(UAdventurePluginGameContext* GameContextOverride, FQuestGraphInteger QuestIntegerVariable, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("GetQuestInteger")))
	{
		return 0;
	}
	if (!IsValid(QuestIntegerVariable.Quest))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestLibrary_GetQuestInteger_QuestNull", "GetQuestInteger:Quest is null or invalid."));
		return 0;
	}
	return QuestIntegerVariable.Quest->GetInteger(GameContext, QuestIntegerVariable.IntegerName);
}

void UAdventurePluginQuestBlueprintLibrary::SetQuestInteger(UAdventurePluginGameContext* GameContextOverride, FQuestGraphInteger QuestIntegerVariable, int32 NewValue, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("SetQuestInteger")))
	{
		return;
	}
	if (!IsValid(QuestIntegerVariable.Quest))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestLibrary_SetQuestInteger_QuestNull", "SetQuestInteger:Quest is null or invalid."));
		return;
	}
	QuestIntegerVariable.Quest->SetInteger(GameContext, QuestIntegerVariable.IntegerName, NewValue);
}

FString UAdventurePluginQuestBlueprintLibrary::GetQuestString(UAdventurePluginGameContext* GameContextOverride, FQuestGraphString QuestStringVariable, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("GetQuestString")))
	{
		return FString();
	}
	if (!IsValid(QuestStringVariable.Quest))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestLibrary_GetQuestString_QuestNull", "GetQuestString:Quest is null or invalid."));
		return FString();
	}
	return QuestStringVariable.Quest->GetString(GameContext, QuestStringVariable.StringName);
}

void UAdventurePluginQuestBlueprintLibrary::SetQuestString(UAdventurePluginGameContext* GameContextOverride, FQuestGraphString QuestStringVariable, const FString& NewValue, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("SetQuestString")))
	{
		return;
	}
	if (!IsValid(QuestStringVariable.Quest))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestLibrary_SetQuestString_QuestNull", "SetQuestString:Quest is null or invalid"));
		return;
	}
	QuestStringVariable.Quest->SetString(GameContext, QuestStringVariable.StringName, NewValue);
}

bool UAdventurePluginQuestBlueprintLibrary::BindQuestEvent(UAdventurePluginGameContext* GameContextOverride, FQuestGraphEvent QuestEvent, FQuestEvent QuestEventHandler, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("BindQuestEvent")))
	{
		return false;
	}

	if (!IsValid(QuestEvent.Quest))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestLibrary_BindQuestEvent_QuestGraphInvalid", "Bind event::graph is invalid"));
		return false;
	}

	TMap<FName, FQuestEvent>& QuestEventsMap = QuestEvent.Quest->QuestEvents;
	if (!QuestEventsMap.Contains(QuestEvent.EventName))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestLibrary_BindQuestEvent_EventNameUndefined", "Bind event::event name is not defined in quest"));
		return false;
	}

	QuestEventsMap.Add(QuestEvent.EventName, QuestEventHandler);
	return true;
}

void UAdventurePluginQuestBlueprintLibrary::FireQuestEvent(UAdventurePluginGameContext* GameContextOverride, FQuestGraphEvent QuestEvent, UObject* WorldObjectContext)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, WorldObjectContext);
	if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("FireQuestEvent")))
	{
		return;
	}

	if (!IsValid(QuestEvent.Quest))
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestLibrary_FireQuestEvent_QuestGraphInvalid", "Fire event::graph is invalid"));
		return;
	}

	FQuestEvent* Event = QuestEvent.Quest->QuestEvents.Find(QuestEvent.EventName);
	if (!Event)
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestLibrary_FireQuestEvent_EventNameUndefined", "Fire event::event name is not defined in quest"));
		return;
	}

	if (!Event->IsBound())
	{
		LOG_Error(NSLOCTEXT("AdventurePlugin", "QuestLibrary_FireQuestEvent_EventUnbound", "Fire event::Event is not bound"));
		return;
	}

	Event->ExecuteIfBound();
}