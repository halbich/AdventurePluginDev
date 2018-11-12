#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "DialogGraphNode_SetString.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SetString : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SetString()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Set string variable");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	UQuestGraph* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	FName StringName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	FString Constant;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_SetString", "NodeTitle", "Set \"{0}\" in \"{1}\" to \"{2}\""), 
			FText::FromName(StringName), 
			FText::FromString(IsValid(Quest) ? Quest->Name : "<EMPTY>"),
			FText::FromString(Constant));
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
		if (!IsValid(Quest)) return true;
		Quest->SetString(StringName, Constant);
		return true;
	};
};
