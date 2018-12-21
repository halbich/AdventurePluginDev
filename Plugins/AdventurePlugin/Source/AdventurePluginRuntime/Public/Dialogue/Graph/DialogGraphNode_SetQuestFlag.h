#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "StoryEngine/Structs/QuestGraphFlag.h"
#include "DialogGraphNode_SetQuestFlag.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SetQuestFlag : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SetQuestFlag()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Set Quest Flag");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	FQuestGraphFlag Flag;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_SetQuestFlag", "NodeTitle", "Set \"{0}\" in \"{1}\""), 
			FText::FromName(Flag.FlagName), 
			FText::FromString(IsValid(Flag.Quest) ? Flag.Quest->Name : "<EMPTY>"));
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor(0, 1, 1);
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

#endif

	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		// TODO
		if (!IsValid(Flag.Quest)) return true;
		Flag.Quest->SetFlag(context, Flag.FlagName);


		return true;
	};
};
