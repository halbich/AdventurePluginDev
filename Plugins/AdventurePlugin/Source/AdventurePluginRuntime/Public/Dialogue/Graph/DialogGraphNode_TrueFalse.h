#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.generated.h"

class UDialogueController;
class UAdventurePluginGameContext;


UCLASS(Abstract)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_TrueFalse : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_TrueFalse()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "BranchingCategory", "Branching");
#endif
	}

	UPROPERTY(BlueprintReadOnly)
	UDialogGraphNode* ChildTrue;

	UPROPERTY(BlueprintReadOnly)
	UDialogGraphNode* ChildFalse;

	virtual void ResetSpecialChildren() override
	{
		ChildTrue = nullptr;
		ChildFalse = nullptr;
	}
};
