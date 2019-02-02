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
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "ManipulationCategory", "Data Manipulation");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SwitchBoolNode")
		FQuestGraphBool Bool;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_SwitchBool", "NodeTitle", "SWITCH {0}->{1}"),
			FText::FromString(IsValid(Bool.Quest) ? Bool.Quest->Name : "<EMPTY>"),
			FText::FromName(Bool.BoolName));
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
		bool value = Bool.Quest->GetBool(context, Bool.BoolName);
		Bool.Quest->SetBool(context, Bool.BoolName, !value);
		return true;
	};
};
