#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "StoryEngine/Structs/QuestGraphString.h"
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
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "ManipulationCategory", "Data Manipulation");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetStringNode")
	FQuestGraphString String;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetStringNode")
	FString Constant;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_SetString", "NodeTitle", "SET {0}->{1} TO {2}"),
			FText::FromString(IsValid(String.Quest) ? String.Quest->Name : "<EMPTY>"),
			FText::FromName(String.StringName), 
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
		if (!IsValid(String.Quest)) return true;
		String.Quest->SetString(String.StringName, Constant);
		return true;
	};
};
