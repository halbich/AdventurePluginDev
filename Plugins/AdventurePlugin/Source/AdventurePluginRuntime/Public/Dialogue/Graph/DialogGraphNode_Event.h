#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "AdventurePluginRuntime.h"
#include "DialogGraphNode_Event.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Event : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Event()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Event");
#endif
	}

	virtual ~UDialogGraphNode_Event()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
		UQuestGraph* Quest;

	UPROPERTY(EditAnywhere, Category = "DialogGraphNode_Editor")
		FName EventName;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_Event", "Event title", "Fire event: {0}"), FText::FromName(EventName));
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::White;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

	virtual uint32 GetOutputPinsCount() const override
	{
		return 0;
	}

#endif

	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		if (!IsValid(Quest))
		{
			LOG_Warning(NSLOCTEXT("DialogGraphNode_Event", "QuestGraphNull", "Execute::Quest graph is NULL"));
			return true;
		}

		auto&& questEvent = Quest->QuestEvents.Find(EventName);
		if (!questEvent)
		{
			LOG_Warning(NSLOCTEXT("DialogGraphNode_Event", "NameNotFound", "Execute::Event name not found in quest"));
			return true;
		}

		if (!questEvent->IsBound())
		{
			LOG_Warning(NSLOCTEXT("DialogGraphNode_Event", "EventUnbound", "Execute::Event is not bound"));
			return true;
		}

		questEvent->ExecuteIfBound();
		return true;
	};
};