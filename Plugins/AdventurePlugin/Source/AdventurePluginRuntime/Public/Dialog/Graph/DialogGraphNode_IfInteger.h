#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphInteger.h"
#include "DialogGraphNode_IfInteger.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfInteger : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfInteger()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Branch on integer variable");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "BranchingCategory", "Branching");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnIntegerNode")
		FQuestGraphInteger Integer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BranchOnIntegerNode")
		int32 Constant;

	UPROPERTY(BlueprintReadOnly)
		UDialogGraphNode* ChildLess;

	UPROPERTY(BlueprintReadOnly)
		UDialogGraphNode* ChildEqual;

	UPROPERTY(BlueprintReadOnly)
		UDialogGraphNode* ChildMore;

	virtual void ResetSpecialChildren() override
	{
		ChildLess = nullptr;
		ChildEqual = nullptr;
		ChildMore = nullptr;
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfInteger", "NodeTitle", "COMPARE {0}->{1} WITH {2}"),
			FText::FromString(IsValid(Integer.Quest) ? Integer.Quest->Name : "<EMPTY>"),
			FText::FromName(Integer.IntegerName),
			Constant);
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

	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(Integer.Quest))
		{
			LOG_Warning(NSLOCTEXT("AP", "DialogGraphNode_IfInteger", "DialogGraphNode_IfInteger:GetNextNode:Quest is null or invalid."));
			return nullptr;
		}
		int32 VariableValue = Integer.Quest->GetInteger(GameContext, Integer.IntegerName);
		if (VariableValue < Constant)
		{
			return ChildLess;
		}
		else if (VariableValue == Constant)
		{
			return ChildEqual;
		}
		else
		{
			return ChildMore;
		}
	}
};
