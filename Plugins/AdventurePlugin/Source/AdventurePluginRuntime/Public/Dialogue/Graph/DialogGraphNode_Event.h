#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "AdventurePluginRuntime.h"
#include "DialogGraphNode_Event.generated.h"

class FDialogEvent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogEvent);

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

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "DialogGraphNode_Editor")
		FDialogEvent Event;

	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		if (Event.IsBound()) Event.Broadcast();
		return true;
	};
};