#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "Quest/Graph/QuestGraph.h"
#include "Quest/Structs/QuestGraphString.h"
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

	virtual bool Execute(UAdventurePluginGameContext* GameContext) override
	{
		if (!IsValid(String.Quest))
		{
			LOG_Warning(NSLOCTEXT("AP", "DialogGraphNode_SetStringQuestInvalid", "DialogGraphNode_SetString:Execute:Quest is null or invalid."));
			return true;
		}
		String.Quest->SetString(GameContext, String.StringName, Constant);
		return true;
	};
};
