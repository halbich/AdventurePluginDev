#pragma once

#include "CoreMinimal.h"
#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_EntryMain.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_EntryMain : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_EntryMain()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Main Entry Point");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "OtherCategory", "Other");
#endif
	}

	virtual ~UDialogGraphNode_EntryMain()
	{
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return NSLOCTEXT("DialogGraphNode_EntryMain", "EntryPoint", "MAIN ENTRY POINT");
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::White;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

	virtual inline bool CanAdd() const override
	{
		return false;
	}

	virtual inline bool CanDelete() const override
	{
		return false;
	}

	virtual inline bool CanDuplicate() const override
	{
		return false;
	}

#endif
};
