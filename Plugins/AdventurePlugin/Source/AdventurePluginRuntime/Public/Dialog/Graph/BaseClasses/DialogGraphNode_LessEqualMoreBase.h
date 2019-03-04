#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_LessEqualMoreBase.generated.h"

class UDialogController;
class UAdventurePluginGameContext;

/**
* Base class for nodes that are branching.
* They have a true or false condition and based on the result will return the correct node when GetNextNode() is called.
*/
UCLASS(Abstract)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_LessEqualMoreBase : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_LessEqualMoreBase()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "BranchingCategory", "Branching");
#endif
	}

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
	* The child with which we should continue if the result of this node is less.
	*/
	UPROPERTY(BlueprintReadOnly)
		UDialogGraphNode* ChildLess;

	/**
	* The child with which we should continue if the result of this node is equal.
	*/
	UPROPERTY(BlueprintReadOnly)
		UDialogGraphNode* ChildEqual;

	/**
	* The child with which we should continue if the result of this node is more.
	*/
	UPROPERTY(BlueprintReadOnly)
		UDialogGraphNode* ChildMore;

	virtual void ResetSpecialChildren() override
	{
		ChildLess = nullptr;
		ChildEqual = nullptr;
		ChildMore = nullptr;
	}
};