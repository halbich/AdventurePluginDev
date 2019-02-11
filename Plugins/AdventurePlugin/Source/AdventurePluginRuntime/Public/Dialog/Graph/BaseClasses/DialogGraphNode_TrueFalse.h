#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.generated.h"

class UDialogController;
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

#if WITH_EDITOR

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::White;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

#endif

	// Specifies whether the expression this node represents is currently true or false. Child classes must override this method.
	virtual bool IsTrue(UAdventurePluginGameContext* GameContext)
	{
		check(false && "This method must be overriden.");
		return false;
	}

	virtual void ResetSpecialChildren() override
	{
		ChildTrue = nullptr;
		ChildFalse = nullptr;
	}

	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* GameContext) override
	{
		return IsTrue(GameContext) ? ChildTrue : ChildFalse;
	}
};
