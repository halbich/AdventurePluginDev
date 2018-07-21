#pragma once

#include "CoreMinimal.h"
#include "GenericGraphRuntime/Public/GenericGraphNode.h"
#include "DialogGraph.h"
#include "DialogGraphNode_EntryMain.generated.h"

UCLASS(Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_EntryMain : public UGenericGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_EntryMain()
	{
#if WITH_EDITORONLY_DATA
		CompatibleGraphType = UDialogGraph::StaticClass();
#endif
	}

	virtual ~UDialogGraphNode_EntryMain()
	{
	}
	
#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return NSLOCTEXT("DialogGraphNode_EntryMain", "EntryPoint", "Entry point");
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::White;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
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
