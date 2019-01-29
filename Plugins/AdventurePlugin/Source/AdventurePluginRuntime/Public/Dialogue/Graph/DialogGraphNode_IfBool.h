#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "StoryEngine/Structs/QuestGraphBool.h"
#include "DialogGraphNode_IfBool.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfBool : public UDialogGraphNode_TrueFalse
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfBool()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Branch on bool variable");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnBoolNode")
		FQuestGraphBool Bool;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfBool", "NodeTitle", "IF {0}->{1}"),
			FText::FromString(IsValid(Bool.Quest) ? Bool.Quest->Name : "<EMPTY>"),
			FText::FromName(Bool.BoolName));
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
		return IsValid(Bool.Quest) && Bool.Quest->GetBool(context, Bool.BoolName)
			? ChildTrue
			: ChildFalse;
	}
};
