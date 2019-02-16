#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "Quest/Graph/QuestGraph.h"
#include "AdventurePluginRuntime.h"
#include "Quest/Structs/QuestGraphEvent.h"
#include "DialogGraphNode_Event.generated.h"
/**
* This node fires an event on a quest.
* It is expected that something on a scene is bound to this event and will handle it. For example it might trigger some cutscene, fight scene etc.
* Note that while this node does have an output pin, it does not wait for the handling to be be done.
* If, for example, you want to play a cutscene and then continue with the dialog, you would stop the execution here and add another entry point.
* After the cutscene you would launch the dialog again from that entry point.
* But you would not do that if for example you wanted to change the weather, etc. If you do not need to wait you would just use the output pin.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Event : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Event()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Event");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "OtherCategory", "Other");
#endif
	}

	virtual ~UDialogGraphNode_Event()
	{
	}
	/**
	* The event to be fired when this node is executed.
	*/
	UPROPERTY(EditAnywhere, Category = "EventNode")
		FQuestGraphEvent Event;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_Event", "Event title", "FIRE EVENT: {0}"), FText::FromName(Event.EventName));
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::White;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

#endif
	/**
	* If quest event is properly defined the execute method will fire that event.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return Always true, firing event never halts the execution of graph.
	*/
	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Event.Quest))
		{
			LOG_Warning(NSLOCTEXT("DialogGraphNode_Event", "QuestGraphNull", "Execute::Quest graph is NULL"));
			return true;
		}

		FQuestEvent* QuestEvent = Event.Quest->QuestEvents.Find(Event.EventName);
		if (!QuestEvent)
		{
			LOG_Warning(NSLOCTEXT("DialogGraphNode_Event", "NameNotFound", "Execute::Event name not found in quest"));
			return true;
		}

		if (!QuestEvent->IsBound())
		{
			LOG_Warning(NSLOCTEXT("DialogGraphNode_Event", "EventUnbound", "Execute::Event is not bound"));
			return true;
		}

		QuestEvent->ExecuteIfBound();
		return true;
	};
};