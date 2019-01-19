#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "StoryEngine/Structs/QuestGraphFlag.h"
#include "DialogGraphNode_IfQuestFlag.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfQuestFlag : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfQuestFlag()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Branch on Quest Flag");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
		FQuestGraphFlag Flag;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfQuestFlag", "NodeTitle", "If \"{0}\" in \"{1}\""), 
			FText::FromName(Flag.FlagName), 
			FText::FromString(IsValid(Flag.Quest) ? Flag.Quest->Name : "<EMPTY>"));
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
		int32 bin = IsValid(Flag.Quest) && Flag.Quest->GetFlag(context, Flag.FlagName) ? 0 : 1;
		return Cast<UDialogGraphNode>(GetFirstChildInBin(bin));
	}
};
