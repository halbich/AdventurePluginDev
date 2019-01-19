#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "StoryEngine/Structs/QuestGraphInteger.h"
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
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	FQuestGraphInteger Integer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
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
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfInteger", "NodeTitle", "Compare \"{0}\" in \"{1}\" with \"{2}\""), 
			FText::FromName(Integer.IntegerName), 
			FText::FromString(IsValid(Integer.Quest) ? Integer.Quest->Name : "<EMPTY>"),
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

	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* context) override
	{
		if (IsValid(Integer.Quest))
		{
			int32 val = Integer.Quest->GetInteger(Integer.IntegerName);
			if (val < Constant) return ChildLess;
			else if (val == Constant) return ChildEqual;
			else return ChildMore;
		}
		return nullptr;
	}
};
