#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "DialogGraphNode_IncrementInteger.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IncrementInteger : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IncrementInteger()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Increment integer variable");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	UQuestGraph* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	FName IntegerName;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IncrementInteger", "NodeTitle", "Increment \"{0}\" in \"{1}\""), 
			FText::FromName(IntegerName), 
			FText::FromString(IsValid(Quest) ? Quest->Name : "<EMPTY>"));
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor(0, 1, 1);
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

#endif

	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		// TODO
		if (!IsValid(Quest)) return true;
		int32 value = Quest->GetInteger(IntegerName);
		Quest->SetInteger(IntegerName, value + 1);
		return true;
	};
};
