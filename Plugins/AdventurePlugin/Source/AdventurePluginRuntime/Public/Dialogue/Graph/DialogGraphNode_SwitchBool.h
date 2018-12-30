#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "StoryEngine/Structs/QuestGraphBool.h"
#include "DialogGraphNode_SwitchBool.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_SwitchBool : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_SwitchBool()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Switch value of bool variable");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	FQuestGraphBool Bool;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_SwitchBool", "NodeTitle", "Switch \"{0}\" in \"{1}\""), 
			FText::FromName(Bool.BoolName), 
			FText::FromString(IsValid(Bool.Quest) ? Bool.Quest->Name : "<EMPTY>"));
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
		if (!IsValid(Bool.Quest)) return true;
		bool value = Bool.Quest->GetBool(Bool.BoolName);
		Bool.Quest->SetBool(Bool.BoolName, !value);
		return true;
	};
};
