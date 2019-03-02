#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_Comment.generated.h"

/**
* This node does nothing. It is just a comment and should just be used to make a graph more readable.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Comment : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Comment()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Comment");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "OtherCategory", "Other");
#endif
	}

	/**
	* The text to be displayed in the comment node.
	*/
	UPROPERTY(EditAnywhere, Category = "CommentNode")
	FText Text;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return Text;
	}

	virtual void SetNodeTitle(const FText& NewTitle) override
	{
		Text = NewTitle;
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor(1, 0, 1);
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

	virtual bool CanRename() const override
	{
		return true;
	}

#endif
};
