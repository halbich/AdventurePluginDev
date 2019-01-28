#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "NodeInterfaces/DialogueNodeShowLineCallbackInterface.h"
#include "DialogGraph.h"
#include "DialogGraphNode_PlayerLineOption.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_PlayerLineOption : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_PlayerLineOption()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Player Line Option");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "LineCategory", "Lines");
#endif
		OptionText = NSLOCTEXT("DialogGraphNode_PlayerLineOption", "DefaultDialog", "<Insert something clever>");
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerLineOptionNode")
		FText OptionText;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return OptionText;
	}

	virtual void SetNodeTitle(const FText& NewTitle) override
	{
		OptionText = NewTitle;
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Green;
	}

	virtual bool CanRename() const override
	{
		return true;
	}

#endif


	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		return true;
	}

	virtual bool IsDialogOption() const override
	{
		return true;
	}

	virtual FDialogLineData GetDialogLine(UAdventurePluginGameContext* Context) const override
	{
		auto toReturn = FDialogLineData();
		toReturn.OptionText = OptionText;
		auto* graph = GetDialogGraph();
		toReturn.SpeakerCharacter = graph->GetDialogPlayerCharacterInstance(Context);
		return toReturn;
	}
};
