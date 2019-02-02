#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "StoryEngine/Structs/QuestGraphString.h"
#include "DialogGraphNode_IfString.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfString : public UDialogGraphNode_TrueFalse
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfString()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Branch on string variable");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnStringNode")
	FQuestGraphString String;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnStringNode")
	FString Constant;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfString", "NodeTitle", "IF {0}->{1} IS {2}"), 
			FText::FromString(IsValid(String.Quest) ? String.Quest->Name : "<EMPTY>"),
			FText::FromName(String.StringName), 
			FText::FromString(Constant));
	}

#endif
	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override
	{
		return IsValid(String.Quest) && Constant.Compare(String.Quest->GetString(GameContext, String.StringName)) == 0;
	}
};
