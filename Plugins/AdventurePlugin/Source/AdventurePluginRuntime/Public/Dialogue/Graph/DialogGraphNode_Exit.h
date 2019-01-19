#pragma once

#include "CoreMinimal.h"
#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_Exit.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Exit : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Exit()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Exit");
#endif
	}

	virtual ~UDialogGraphNode_Exit()
	{
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::FromString("Exit");
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::White;
	}

#endif
};
