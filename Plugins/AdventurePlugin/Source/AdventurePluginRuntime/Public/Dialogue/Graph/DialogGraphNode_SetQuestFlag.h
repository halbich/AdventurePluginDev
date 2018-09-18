#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "DialogGraphNode_SetQuestFlag.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SetQuestFlag : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SetQuestFlag()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Set Quest Flag");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	UQuestGraph* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	FName FlagName;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_SetQuestFlag", "NodeTitle", "Set \"{0}\" in \"{1}\""), 
			FText::FromName(FlagName), 
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
		Quest->SetFlag(FlagName);


		return true;
	};
};
