#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "StoryEngine/Graph/QuestGraph.h"
#include "StoryEngine/Structs/QuestGraphBool.h"
#include "DialogGraphNode_IfBool.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_IfBool : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_IfBool()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Branch on bool variable");
#endif
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
	FQuestGraphBool Bool;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_IfBool", "NodeTitle", "If \"{0}\" in \"{1}\" is true"), 
			FText::FromName(Bool.BoolName), 
			FText::FromString(IsValid(Bool.Quest) ? Bool.Quest->Name : "<EMPTY>"));
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

	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* context) override
	{
		int32 bin = IsValid(Bool.Quest) && Bool.Quest->GetBool(Bool.BoolName) ? 0 : 1;
		return Cast<UDialogGraphNode>(GetFirstChildInBin(bin));
	}
};
