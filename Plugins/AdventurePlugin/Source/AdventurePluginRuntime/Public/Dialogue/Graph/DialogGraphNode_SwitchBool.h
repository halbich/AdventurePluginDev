#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "DialogGraphNode_SwitchBool.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SwitchBool : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SwitchBool()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Switch value of bool variable");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	UQuestGraph* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	FName BoolName;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_SwitchBool", "NodeTitle", "Switch \"{0}\" in \"{1}\""), 
			FText::FromName(BoolName), 
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

	virtual bool Execute(UDialogueController* controller, IDialoguePresenterInterface* widget) override
	{
		// TODO
		if (!IsValid(Quest)) return true;
		bool value = Quest->GetBool(BoolName);
		Quest->SetBool(BoolName, !value);
		return true;
	};
};
