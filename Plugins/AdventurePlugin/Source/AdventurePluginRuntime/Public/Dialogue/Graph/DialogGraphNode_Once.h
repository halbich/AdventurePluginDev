#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_Once.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Once : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Once()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Once");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "BranchingCategory", "Branching");
#endif
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return NSLOCTEXT("DialogGraphNode_Once","Once","ONCE");
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
};
