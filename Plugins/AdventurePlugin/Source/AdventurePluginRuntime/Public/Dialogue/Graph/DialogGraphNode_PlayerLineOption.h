#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "NodeInterfaces/DialogueNodeShowLineCallbackInterface.h"
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
#endif
		OptionText = NSLOCTEXT("DialogGraphNode_PlayerLineOption", "DefaultDialog", "<Insert something clever>");
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogGraphNode_Editor")
		FText OptionText;

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_PlayerLineOption", "PlayerLineOptionSay", "Player: \"{0}\""), OptionText);
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Green;
	}
#endif


	virtual bool Execute(UDialogueController* controller, IDialoguePresenterInterface* widget) override
	{
		return true;
	}

	virtual bool IsDialogOption() const override
	{
		return true;
	}

	virtual FDialogLineData GetDialogLine() const override
	{
		auto toReturn = FDialogLineData();
		toReturn.OptionText = OptionText;
		toReturn.IsPlayerCharacterLine = true;
		return toReturn;
	}
};
