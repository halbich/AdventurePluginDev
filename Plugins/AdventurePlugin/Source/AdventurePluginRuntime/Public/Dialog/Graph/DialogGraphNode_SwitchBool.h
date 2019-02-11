#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphBool.h"
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

	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		// TODO
		if (!IsValid(Bool.Quest))
		{
			return true;
		}
		bool bOldValue = Bool.Quest->GetBool(GameContext, Bool.BoolName);
		Bool.Quest->SetBool(GameContext, Bool.BoolName, !bOldValue);
		return true;
	};
};
