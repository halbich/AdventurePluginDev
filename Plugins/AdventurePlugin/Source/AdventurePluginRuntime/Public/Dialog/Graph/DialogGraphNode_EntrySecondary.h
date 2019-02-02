#pragma once

#include "CoreMinimal.h"
#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_EntrySecondary.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_EntrySecondary : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_EntrySecondary()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Secondary Entry Point");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "OtherCategory", "Other");
#endif
	}

	virtual ~UDialogGraphNode_EntrySecondary()
	{
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		if (Id.IsNone())
		{
			return NSLOCTEXT("DialogGraphNode_EntrySecondary", "Secondary entry point no id title", "ENTRY POINT: No Id set");
		}
		else
		{
			return FText::Format(NSLOCTEXT("DialogGraphNode_EntrySecondary", "Secondary entry point title", "ENTRY POINT: {0}"), FText::FromName(Id));
		}
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