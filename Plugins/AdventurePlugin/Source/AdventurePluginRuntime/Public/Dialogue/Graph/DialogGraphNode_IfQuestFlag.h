#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "DialogGraphNode_IfQuestFlag.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfQuestFlag : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfQuestFlag()
	{
		ContextMenuName = FText::FromString("Branch on Quest Flag");
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	UQuestGraph* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	FName FlagName;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfQuestFlag", "NodeTitle", "If \"{0}\" in \"{1}\""), 
			FText::FromName(FlagName), 
			FText::FromString(IsValid(Quest) ? Quest->Name : "<EMPTY>"));
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

	virtual uint32 GetOutputPinsCount() const override
	{
		return 2;
	}

	virtual UDialogGraphNode* GetNextNode() override
	{
		int32 index = IsValid(Quest) && Quest->GetFlag(FlagName) ? 0 : 1;
		return ChildrenNodes.Num() > index ? Cast<UDialogGraphNode>(ChildrenNodes[index]) : nullptr;
	}
};
