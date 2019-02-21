#pragma once

#include "CoreMinimal.h"
#include "QuestGraphNode.h"
#include "QuestGraphNode_Comment.generated.h"
/**
* This node represents just a commentary, does nothing, is true when its predecessors are true.
* Exists just to make a graph more readable.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UQuestGraphNode_Comment : public UQuestGraphNode
{
	GENERATED_BODY()

public:

	UQuestGraphNode_Comment()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = NSLOCTEXT("QuestGraphNode_Comment", "ContextMenuName", "Comment");
#endif
	}
	/**
	* The text that should be displayed in the comment node.
	*/
	UPROPERTY(EditAnywhere, Category = "CommentNode")
	FText Text;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const override
	{
		return Text;
	}

	virtual void SetNodeTitle(const FText& NewTitle) override
	{
		Text = NewTitle;
	}

	virtual bool IsTrue(UAdventurePluginGameContext* GameContext) override {
		return ParentNodesTrue(GameContext);
	}

	virtual inline FLinearColor GetBackgroundColor() const override
	{
		return FLinearColor(1, 0, 1);
	}

	virtual inline bool CanRename() const override
	{
		return true;
	}

#endif
};
