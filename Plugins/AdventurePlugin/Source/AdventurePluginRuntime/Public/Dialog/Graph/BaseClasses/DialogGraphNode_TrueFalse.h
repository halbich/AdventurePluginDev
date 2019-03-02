#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_TrueFalse.generated.h"

class UDialogController;
class UAdventurePluginGameContext;

/**
* Base class for nodes that are branching. 
* They have a true or false condition and based on the result will return the correct node when GetNextNode is called.
*/
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

	/**
	* The next node if this node is true.
	*/
	UPROPERTY(BlueprintReadOnly)
	UDialogGraphNode* ChildTrue;

	/**
	* The next node if this node is false.
	*/
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

	/**
	* Specifies whether the expression this node represents is currently true or false. Child classes must override this method.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if this node is true, otherwise false.
	*/
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

	/**
	* Returns the next node to be executed. 
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return ChildTrue if IsTrue is true, otherwise ChildFalse.
	*/
	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* GameContext) override
	{
		return IsTrue(GameContext) ? ChildTrue : ChildFalse;
	}
};
