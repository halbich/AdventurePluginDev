#pragma once

#include "CoreMinimal.h"
#include "QuestGraphNode.h"
#include "QuestGraphNode_Flag.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UQuestGraphNode_Flag : public UQuestGraphNode
{
	GENERATED_BODY()

public:

	UQuestGraphNode_Flag()
	{
		ContextMenuName = NSLOCTEXT("QuestGraphNode_Flag", "ContextMenuName", "Simple flag");
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestGraphNode_Editor")
	FName FlagName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestGraphNode_Editor")
	bool FlagValue;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::FromName(FlagName);
	}

	virtual void SetNodeTitle(const FText & NewTitle)
	{
		FlagName = FName(*NewTitle.ToString());
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Yellow;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

#endif
};
