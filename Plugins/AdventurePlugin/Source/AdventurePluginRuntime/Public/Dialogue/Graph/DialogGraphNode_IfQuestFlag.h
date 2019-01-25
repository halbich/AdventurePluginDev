#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "StoryEngine/Structs/QuestGraphFlag.h"
#include "DialogGraphNode_IfQuestFlag.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfQuestFlag : public UDialogGraphNode_TrueFalse
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfQuestFlag()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Branch on Quest Flag");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnFlagNode")
		FQuestGraphFlag Flag;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfQuestFlag", "NodeTitle", "IF {0}->{1}"), 
			FText::FromString(IsValid(Flag.Quest) ? Flag.Quest->Name : "<EMPTY>"),
			FText::FromName(Flag.FlagName));
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

	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* context) override
	{
		return IsValid(Flag.Quest) && Flag.Quest->GetFlag(context, Flag.FlagName)
			? ChildTrue
			: ChildFalse;
	}
};
