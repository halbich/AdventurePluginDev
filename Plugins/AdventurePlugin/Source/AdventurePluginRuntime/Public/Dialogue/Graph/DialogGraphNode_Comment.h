#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_Comment.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Comment : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Comment()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Comment");
#endif
	}

	UPROPERTY(EditAnywhere, Category = "DialogGraphNode_Editor")
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

#endif
};
