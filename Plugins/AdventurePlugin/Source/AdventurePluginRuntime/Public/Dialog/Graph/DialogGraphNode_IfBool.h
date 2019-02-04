#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphBool.h"
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

#endif

	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		return IsValid(Bool.Quest) && Bool.Quest->GetBool(GameContext, Bool.BoolName);
	}
};
